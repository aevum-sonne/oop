#pragma once

#include <Protocol/Protocol.h>
#include <string>
#include <vector>
#include <regex>

class HttpUrl
{
public:
    explicit HttpUrl(const std::string& url);

    HttpUrl(const std::string& domain,
            const std::string& document,
            Protocol protocol = HTTP);

    HttpUrl(const std::string& domain,
            const std::string& document,
            Protocol protocol,
            unsigned short port);

    void Print(std::ostream& output);

    [[nodiscard]] std::string GetURL() const;
    [[nodiscard]] std::string GetDomain() const;
    [[nodiscard]] std::string GetDocument() const;
    [[nodiscard]] Protocol GetProtocol() const;
    [[nodiscard]] unsigned short GetPort() const;

private:
    void ValidateProtocol(const std::string& protocol);
    void ValidateDomain(const std::string& domain);
    void ValidatePort(int port);
    void ValidateDocument(const std::string& document);
    void ValidateUrl(const std::string& url);

    std::smatch SplitUrl(const std::string& url);

    void SetDefaultPort(Protocol protocol);

    static Protocol StringToProtocol(const std::string& string);
    static std::string ProtocolToString(const Protocol& protocol);
    static std::string ToLowerCase(std::string string);

    const unsigned short URL_COMPONENTS_COUNT = 5;

    std::string m_url, m_domain, m_document;
    Protocol m_protocol;
    unsigned short m_port;
};