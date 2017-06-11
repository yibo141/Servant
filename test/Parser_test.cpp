#include <iostream>
#include <string>
#include "../Parser.h"

using namespace std;

int main()
{
    string request = "GET /index.html HTTP/1.1\r\nHost: www.zhihu.com\r\nConnection: keep-alive\r\n";
    Parser p(request);
    HTTPRequest result = p.getParseResult();
    cout << "Method: " << result.method << endl;
    cout << "URI: " << result.uri << endl;
    cout << "Version: " << result.version << endl;
    cout << "Host: " << result.host << endl;
    cout << "Connection: " << result.connection << endl;
    return 0;
}