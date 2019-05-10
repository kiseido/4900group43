#include "stdafx.h"
//#include "CppUnitTest.h"
//#include "../4900group43/Network.hpp";
//#include "../4900group43/Network.cpp";
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTests
//{		
//	TEST_CLASS(NetworkTests)
//	{
//	public:
//		
//		TEST_METHOD(InitWinsockReturn)
//		{
//			WSADATA wsa;
//			int ret = initWinsockLibrary(&wsa);
//			Assert::AreEqual(0, ret);
//		}
//
//		TEST_METHOD(CreateSocketReturn)
//		{
//			SOCKET s;
//			int ret = createSocket(&s, 0);
//			Assert::AreEqual(0, ret);
//		}
//
//		TEST_METHOD(NotInitSocket_ServerReturn)
//		{
//			SOCKET s;
//			WSADATA wsa;
//			initWinsockLibrary(&wsa);
//			struct sockaddr_in server;
//
//			//Server Info
//			const char* addr = "172.217.14.195";
//			int family = AF_INET;
//			int port = 80;
//
//			setupServer(&server, addr, family, port);
//			connectToServer(&s, &server);
//			int ret = connectToServer(&s, &server);
//			Assert::AreEqual(1, ret);
//
//		}
//
//		TEST_METHOD(InitializedSocketReturn)
//		{
//			SOCKET s;
//			WSADATA wsa;
//			initWinsockLibrary(&wsa);
//			createSocket(&s, 0);
//
//			struct sockaddr_in server;
//
//			//Server Info
//
//			//Google address
//			const char* addr = "172.217.14.195";
//			int family = AF_INET;
//			int port = 80;
//
//			setupServer(&server, addr, family, port);
//			int ret = connectToServer(&s, &server);
//			Assert::AreEqual(0, ret);
//		}
//
//		TEST_METHOD(SendDataReturn)
//		{
//			SOCKET s;
//			WSADATA wsa;
//			initWinsockLibrary(&wsa);
//			createSocket(&s, 0);
//
//			struct sockaddr_in server;
//
//			//Server Info
//
//			//Google address
//			const char* addr = "172.217.14.195";
//			int family = AF_INET;
//			int port = 80;
//
//			setupServer(&server, addr, family, port);
//			connectToServer(&s, &server);
//
//			char* message = "GET / HTTP/1.1\r\n\r\n";
//			int ret = sendData(&s, message);
//			Assert::AreEqual(0, ret);
//			
//			//char server_reply[2000];
//			//receiveReply(&s, server_reply);
//		}
//
//		TEST_METHOD(ReceiveDataReturn)
//		{
//			SOCKET s;
//			WSADATA wsa;
//			initWinsockLibrary(&wsa);
//			createSocket(&s, 0);
//
//			struct sockaddr_in server;
//
//			//Server Info
//
//			//Google address
//			const char* addr = "172.217.14.195";
//			int family = AF_INET;
//			int port = 80;
//
//			setupServer(&server, addr, family, port);
//			connectToServer(&s, &server);
//
//			char* message = "GET / HTTP/1.1\r\n\r\n";
//			sendData(&s, message);
//
//			char server_reply[10000];
//			int ret = receiveReply(&s, server_reply);
//			Assert::AreEqual(0, ret);
//		}
//
//		TEST_METHOD(GetIPfromGoogle)
//		{
//			char hostName[] = "www.google.ca";
//			WCHAR ip[100];
//			getIPFromDomain(hostName, ip);
//			WCHAR correct1[100] = L"172.217.14.195";
//			WCHAR correct2[100] = L"172.217.14.227";
//			bool res1 = wcscmp(correct1, ip);
//			bool res2 = wcscmp(correct2, ip);
//			bool finalRes = (res1 == true || res2 == true);
//			Assert::AreEqual(finalRes, true);
//		}
//
//		TEST_METHOD(GetIPfromDigitalProjects)
//		{
//			char hostName[] = "www.digitalprojects.info";
//			WCHAR ip[100];
//			getIPFromDomain(hostName, ip);
//			WCHAR correct[100] = L"198.105.215.36";
//			Assert::AreEqual(correct, ip);
//		}
//
//		TEST_METHOD(BindSocketReturn)
//		{
//			SOCKET s;
//			WSADATA wsa;
//			initWinsockLibrary(&wsa);
//			createSocket(&s, 0);
//
//			struct sockaddr_in server;
//
//			//Server Info
//			const char* addr = "127.0.0.1";
//			int family = AF_INET;
//			int port = htons(8888);
//
//			setupServer(&server, addr, family, port);
//
//			int ret = bindSocket(&server, &s);
//
//			closeSocket(&s);
//
//			Assert::AreEqual(0, ret);
//		}
//
//	};
//}