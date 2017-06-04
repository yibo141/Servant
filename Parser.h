/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <string.h>

// 解析请求后的数据存储在http_request结构体中
typedef struct
{
    std::string method;     // 请求的方法
    std::string uri;        // 请求的uri
    std::string version;    // HTTP版本
    std::string host;       // 请求的主机名
    std::string connection; // Connection首部
} HTTPRequest;

class Parser
{
public:
    Parser(const std::string request);
    HTTPRequest getParseResult();
private:
    void parseLine();
    void parseRequestLine();
    void parseHeaders();
    std::string _request;
    std::vector<std::string> _lines;
    HTTPRequest _parseResult;
};

#endif // PARSER_H