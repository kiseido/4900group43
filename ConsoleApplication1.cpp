#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <string>

// XY Coordinates
struct GridLocation {
	int x, y;
};

namespace std {
	/* implement hash function so we can put GridLocation into an unordered_set */
	template <> struct hash<GridLocation> {
		typedef GridLocation argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridLocation& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}

// Helpers for GridLocation

bool operator == (GridLocation a, GridLocation b) {
	return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
	return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
	out << '(' << loc.x << ',' << loc.y << ')';
	return out;
}

/////////////////////////////////////////////////////////////////////////// SQUARE 
struct SquareGrid {
	static std::array<GridLocation, 8> DIRS;

	// Instance variables
	int width, height;
	std::unordered_set<GridLocation> walls;

	// Constructor
	SquareGrid(int width_, int height_)
		: width(width_), height(height_) {}

	// Methods 
	bool in_bounds(GridLocation id) const {
		return 0 <= id.x && id.x < width
			&& 0 <= id.y && id.y < height;
	}

	bool passable(GridLocation id) const {
		return walls.find(id) == walls.end();
	}

	void addWall(int x, int y) {
		walls.insert(GridLocation{ x, y });
	}

	std::vector<GridLocation> neighbors(GridLocation id) const {
		std::vector<GridLocation> results;

		for (GridLocation dir : DIRS) {
			GridLocation next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next) && passable(next)) {
				results.push_back(next);
			}
		}

		if ((id.x + id.y) % 2 == 0) {
			// aesthetic improvement on square grids
			std::reverse(results.begin(), results.end());
		}

		return results;
	}

	double cost(GridLocation from_node, GridLocation to_node) const {
		return 1.0;
	}

};

std::array<GridLocation, 8> SquareGrid::DIRS =
{ GridLocation{0, -1}, GridLocation{1, -1}, GridLocation{1, 0}, GridLocation{1, 1},
  GridLocation{0, 1}, GridLocation{-1, 1}, GridLocation{-1, 0}, GridLocation{-1, -1}
};


///////////////////////////////////////////////////////// Drawing a grid

// This outputs a grid. 
// Pass in a distances map if you want to print the distances
// pass in a point_to map if you want to print arrows that point to the parent location, 
// pass in a path vector if you want to draw the path.
template<class Graph>
void draw_grid(const Graph& graph, int field_width,
	std::unordered_map<GridLocation, double>* distances = nullptr,
	std::unordered_map<GridLocation, GridLocation>* point_to = nullptr,
	std::vector<GridLocation>* path = nullptr) {
	for (int y = 0; y != graph.height; ++y) {
		for (int x = 0; x != graph.width; ++x) {
			GridLocation id{ x, y };
			std::cout << std::left << std::setw(field_width);
			if (graph.walls.find(id) != graph.walls.end()) {
				std::cout << std::string(field_width, '#');
			}
			else if (point_to != nullptr && point_to->count(id)) {
				GridLocation next = (*point_to)[id];
				if (next.x == x + 1 && next.y == y - 1) {std::cout << "/ "; }
				else if (next.x == x - 1 && next.y == y + 1) {std::cout << "\\ "; }
				else if (next.x == x + 1) { std::cout << "> "; }
				else if (next.x == x - 1) { std::cout << "< "; }
				else if (next.y == y + 1) { std::cout << "v "; }
				else if (next.y == y - 1) { std::cout << "^ "; }
				else { std::cout << "* "; }
			}
			else if (distances != nullptr && distances->count(id)) {
				std::cout << (*distances)[id];
			}
			else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
				std::cout << '@';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
	for (int x = x1; x < x2; ++x) {
		for (int y = y1; y < y2; ++y) {
			grid.walls.insert(GridLocation{ x, y });
		}
	}
}

SquareGrid testSquareGrid() {
	SquareGrid grid(30, 15);
	add_rect(grid, 3, 3, 5, 12);
	add_rect(grid, 13, 4, 15, 15);
	add_rect(grid, 21, 0, 23, 7);
	add_rect(grid, 23, 5, 26, 7);
	return grid;
}

//////////////////////////////////////////////////////////////////////// SQUARE (WEIGHED) 
struct GridWithWeights : SquareGrid {
	std::unordered_set<GridLocation> forests;
	GridWithWeights(int w, int h) : SquareGrid(w, h) {}
	double cost(GridLocation from_node, GridLocation to_node) const {
		return forests.find(to_node) != forests.end() ? 5 : 1;
	}
};

GridWithWeights testWeightedSquareGrid() {
	GridWithWeights grid(10, 10);
	add_rect(grid, 1, 7, 4, 9);
	typedef GridLocation L;
	grid.forests = std::unordered_set<GridLocation>{
	  L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
	  L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
	  L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
	  L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
	  L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
	  L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
	  L{7, 3}, L{7, 4}, L{7, 5}
	};
	return grid;
}

///////////////////////////////////////////////////////////////////////// HEX
struct HexGrid {
	// Directions N NE SE S SW NW
	std::array<GridLocation, 6> DIRS =
	{ GridLocation{0,-1}, GridLocation{1, -1}, GridLocation{1, 0},
	GridLocation{0, 1}, GridLocation{-1, 1}, GridLocation{-1, 0}
	};
	//std::array<GridLocation, 6> DIRS =
	//{ GridLocation{0,-1}, GridLocation{1, 0}, GridLocation{-1, -1},
	//GridLocation{0, 1}, GridLocation{-1, 0}, GridLocation{1, 1}
	//};

	int width, height;						// Size of Board 
	std::unordered_set<GridLocation> walls;	// Blocked coordinates 

	// Pointy top?
	HexGrid(int width_, int height_)			// Rectangular Hex Board 
		: width(width_), height(height_) {
		int padding = (height - 1) / 2;
		for (int h = 0; h < height; h++) {
			int paddingFront = padding - h / 2;
			for (int b = 0; b < paddingFront; b++) {
				walls.insert(GridLocation{ b,h });
			}
			for (int e = width + paddingFront; e < width + padding; e++) {
				walls.insert(GridLocation{ e,h });
			}
		}
		width += (height - 1) / 2;
	}

	// Flat top
	// width = N	height = width + (width - 1) / 2 
	// max padding = width -1 

	HexGrid(int width_)			// Rectangular Hex Board 
		: width(width_) {
		height = width + (width - 1) / 2;
		int hPadding = (width - 1) / 2;
		int b = 1;
		for (int h = 0; h < hPadding; h++) {
			for (int s = b; s < width; s++) {
				walls.insert(GridLocation{ s,h });
			}
			for (int i = 0; i < b; i++) {
				walls.insert(GridLocation{ i,(height - 1) - h});	
			}
			b += 2;
		}
	}

	bool in_bounds(GridLocation id) const {	// Coordinates Inbounds Check
		return 0 <= id.x && id.x < width //+ ((height - 1) / 2)	//	Padding Rectangular Board
			&& 0 <= id.y && id.y < height; //+((height - 1) / 2);
	}

	bool passable(GridLocation id) const {	// Not Blocked Coordinate Check
		return walls.find(id) == walls.end();
	}

	std::vector<GridLocation> neighbors(GridLocation id) const {	// All Valid Neighbors
		std::vector<GridLocation> results;

		for (GridLocation dir : DIRS) {
			GridLocation next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next) && passable(next)) {
				results.push_back(next);
			}
		}

		return results;
	};

	std::unordered_set<GridLocation> forests;
	std::unordered_set<GridLocation> river;

	void addForests(std::unordered_set<GridLocation> forests_) {
		forests = forests_;
	}

	void addRiver(std::unordered_set<GridLocation> river_) {
		river = river_;
	}

	double cost(GridLocation from_node, GridLocation to_node) const {
		double cost = 0;
		if (forests.find(to_node) != forests.end())
			cost += 5.0;
		else if (river.find(to_node) != river.end())
			cost += 10.0;
		else
			cost += 1;
		return cost;
	}
};

////////////////////////////////////////////////////////////////////// PATHFINDING

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

// Dijkstra with early break 
template<typename Location, typename Graph>
void dijkstra_search
(Graph graph,
	Location start,
	Location goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}
	}
}

// Dijkstra 
template<typename Location, typename Graph>
void dijkstra_search
(Graph graph,
	Location start,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		for (Location next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}
	}
}

// PATH
template<typename Location>
std::vector<Location> reconstruct_path(
	Location start, Location goal,
	std::unordered_map<Location, Location> came_from
) {
	std::vector<Location> path;
	Location current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

template<typename Location>
Location movement(
	std::vector<Location> path, double stamina,
	std::unordered_map<Location, double> cost
) {
	Location moveTo = path[0];	// start	
	double current = cost[moveTo];
	int i = 1;
	int max = path.size();
	while (current < stamina && i < max ) {
		moveTo = path[i];
		current = cost[moveTo];
		i++;
	}
	return moveTo;
}

// Heuristic Function
inline double heuristic(GridLocation a, GridLocation b) {
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// Location = GridLocation	Graph = Grid
template<typename Location, typename Graph>
void a_star_search
(Graph graph,
	Location start,
	Location goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////// Gameloop 

/* Globals */
bool gameover = false;

struct Piece {
	int type;	//  FAST, AVERAGE, SLOW
	int health;
	int power;
	int stamina;
	int speed; 
	GridLocation coord;

	Piece() {};
	Piece(int type_) : type(type_) {
		switch(type_) {
		case 0 :			// FAST
			health = 3;
			power = 1;
			stamina = 15;
			speed = 15;	
			break;
		case 1 :			// AVERAGE
			health = 5;
			power = 2;
			stamina = 10;
			speed = 10;	
			break;
		case 2 :			// SLOW
			health = 10;
			power = 3;
			stamina = 5;
			speed = 5; 
			break;
		default : 
			break;
		}
	};

	int maxHealth[3] = { 3,5,10 };

	double healthPercent() {
		return (double)health / (double)maxHealth[type];
	};

	bool isBattle(GridLocation moveTo, Piece selected, Piece player) {
		selected.coord = moveTo;
		return moveTo == player.coord;
	};
};

struct Player {
	bool turn;
	std::vector<Piece> available;
	std::vector<Piece> captured; 
	
	Player() {};
	Player(bool turn, std::vector<Piece> selection) : turn(turn), available(selection) {};
 
	void endTurn(Player players[2]) {
		players[0].turn = !players[0].turn;
		players[1].turn = !players[1].turn;
	}
};

//Hexboard AI 
//-Piece toMove
//- double cost;
//-For all cpu pieces
//dijkstra
//for all player pieces
//if player piece cost < cost
//	toMove = this;
//cost = this;
template<typename Graph>
bool aiHexMove(Graph grid, std::vector<Piece> allies, std::vector<Piece> enemies ) {
	Piece selected; 
	Piece target;
	double cost = DBL_MAX;
	GridLocation moveTo;

	for (Piece ally: allies) {
		std::unordered_map<GridLocation, GridLocation> came_from;
		std::unordered_map<GridLocation, double> cost_so_far;
		dijkstra_search(grid, ally.coord, came_from, cost_so_far);
		
		// need to save selected and target - target()
		for (Piece player : enemies) {
			if (cost_so_far.at(player.coord) < cost) {
				cost = cost_so_far.at(player.coord);
				target = player;
				selected = ally;
			}
		}
		std::vector<GridLocation> path = reconstruct_path(selected.coord, target.coord, came_from);
		moveTo = movement(path, selected.stamina, cost_so_far);
	}
	// have a start and a goal
	return selected.isBattle(moveTo, selected, target);
}

// Game
int runGame(Player player, Player cpu) {
	bool gameover = false;

	std::vector<Piece> selectionCPU = {Piece(0), Piece(1), Piece(3)};
	// initialize coordinates 
	selectionCPU[0].coord = GridLocation();
	selectionCPU[1].coord = GridLocation();
	selectionCPU[2].coord = GridLocation();

	std::vector<Piece> selectionPlayer = { Piece(0), Piece(1), Piece(3) };
	selectionPlayer[0].coord = GridLocation();
	selectionPlayer[1].coord = GridLocation();
	selectionPlayer[2].coord = GridLocation();

	// set start coordinates for all pieces 
	HexGrid board = HexGrid(7);
	Player players[2] = { player, cpu };

	while (!gameover) {
		if (players[0].turn) {
			// User actions 
			players[0].endTurn(players); // End turn button
		}
		else if (players[1].turn) {		// cpu
			if (aiHexMove(board, selectionCPU, selectionPlayer)) {
				// enter combat 
				// destroy losing unit 
				// update health of winning unit
			}
			players[1].endTurn(players);
		}

	}
	return 1;
}


int main()
{
	GridLocation start = GridLocation{ 0,0 };
	GridLocation goal = GridLocation{ 9,4 };
	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;

	GridWithWeights test = testWeightedSquareGrid();
	dijkstra_search(test, start, came_from, cost_so_far);
	draw_grid(test, 10, &cost_so_far);

	std::cout << "\n";

	std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
	draw_grid(test, 10, NULL, NULL, &path);

	std::cout << "\n";

	std::unordered_map<GridLocation, GridLocation> came_from_;
	std::unordered_map<GridLocation, double> cost_so_far_;
	a_star_search(test, start, goal, came_from_, cost_so_far_);
	draw_grid(test, 10, &cost_so_far_);

	std::cout << "\n";

	path = reconstruct_path(start, goal, came_from_);
	draw_grid(test, 10, NULL, NULL, &path);

	//std::cout << "\n";

	//draw_grid(test, 10, &cost_so_far_);
	//draw_grid(test, 10, &came_from);

	//HexGrid hexGrid = HexGrid(7, 7);
	//dijkstra_search(hexGrid, start, came_from, cost_so_far);
	//draw_grid(hexGrid, 10);
	//draw_grid(hexGrid, 10, &cost_so_far);
	//draw_grid(hexGrid, 10, 0 , &came_from);
	//std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
	//draw_grid(hexGrid, 10, 0, 0, &path);
	//GridLocation moveTo = movement(path, 1.0, cost_so_far);
	//std::cout << moveTo;
	return 0;
}


/*
Combat AI
- Pathfind to player
- Shoot continuously 
- Shoot in direction of movement 
*/

template<typename Graph>
std::vector<GridLocation> combatAI(Graph board, GridLocation cpu, GridLocation player) {
	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;
	a_star_search(board, cpu, player, came_from, cost_so_far);

	return reconstruct_path(cpu, player, came_from);
}