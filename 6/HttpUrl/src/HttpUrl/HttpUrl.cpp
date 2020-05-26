#include <HttpUrl/HttpUrl.h>
#include <UrlParsingError/UrlParsingError.h>
#include <ParsingMessages/ParsingMessages.h>
#include <limits>
#include <ostream>

HttpUrl::HttpUrl(std::string const& url)
{
    ValidateUrl(ToLowerCase(url));
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
    ValidateDomain(ToLowerCase(domain));
    ValidateDocument(ToLowerCase(document));
    SetDefaultPort(protocol);
    m_protocol = protocol;
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
    ValidateDomain(ToLowerCase(domain));
    ValidateDocument(ToLowerCase(document));
    m_port = port;
    m_protocol = protocol;
}

std::string HttpUrl::GetURL() const
{
    return m_url;
}

std::string HttpUrl::GetDomain() const
{
    return m_domain;
}

std::string HttpUrl::GetDocument() const
{
    return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
    return m_port;
}

void HttpUrl::ValidateProtocol(const std::string& protocol)
{
    if (protocol != "http" && protocol != "https")
    {
        throw UrlParsingError(ParsingMessages::INVALID_PROTOCOL);
    }

    m_protocol = StringToProtocol(protocol);
}

void HttpUrl::ValidateDomain(const std::string& domain)
{
    std::regex regex(R"(^((?!-))(xn--)?[a-z0-9][a-z0-9-_]{0,61}[a-z0-9]{0,1}\.(xn--)?([a-z0-9\-]{1,61}|[a-z0-9-]{1,30}\.[a-z]{2,})$)");

    if (!std::regex_match(domain, regex))
    {
        throw UrlParsingError(ParsingMessages::INVALID_DOMAIN);
    }

    m_domain = domain;
}

void HttpUrl::ValidatePort(const int port)
{
    if (port > std::numeric_limits<unsigned short>::max() || port < 0)
    {
        throw UrlParsingError(ParsingMessages::INVALID_PORT);
    }

    m_port = port;
}

void HttpUrl::ValidateDocument(const std::string& document)
{
    std::string doc = (document[0] == '/') ? document
            : '/' + document;

    std::regex regex(R"(^\/(.+\/)*(.+)\.(.+)$)");
    if (!std::regex_match(doc, regex))
    {
        throw UrlParsingError(ParsingMessages::INVALID_DOCUMENT);
    }

    m_document = std::move(doc);
}

void HttpUrl::ValidateUrl(const std::string& url)
{
    auto urlComponents = SplitUrl(url);

    m_url = urlComponents[0];
    ValidateProtocol(urlComponents[1]);
    ValidateDomain(urlComponents[2]);

    // If port isn't specified, set default port for current protocol
    if (std::string() != urlComponents[3])
    {
        ValidatePort(std::stoi(urlComponents[3]));
    }
    else
    {
        SetDefaultPort(m_protocol);
    }

    // Handle empty document
    if (std::string() != urlComponents[4])
    {
        ValidateDocument(urlComponents[4]);
    }
    else
    {
        m_document = "/";
        m_url += m_document;
    }
}

std::smatch HttpUrl::SplitUrl(const std::string& url)
{
    std::regex regex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)");
    std::smatch smatch;

    if (!std::regex_search(url, smatch, regex))
    {
        throw UrlParsingError(ParsingMessages::INVALID_URL);
    }
    else if (smatch.size() != URL_COMPONENTS_COUNT)
    {
        throw UrlParsingError(ParsingMessages::INVALID_URL_COMPONENTS_COUNT);
    }

    return smatch;
}

void HttpUrl::SetDefaultPort(Protocol protocol)
{
    m_port = (Protocol::HTTP == protocol) ? 80
            : 443;
}

std::string HttpUrl::ToLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return string;
}

Protocol HttpUrl::StringToProtocol(const std::string& string)
{
    return (string == "http") ? Protocol::HTTP
            : Protocol::HTTPS;
}

std::string HttpUrl::ProtocolToString(const Protocol& protocol)
{
    return (Protocol::HTTP == protocol) ? "HTTP"
            : "HTTPS";
}

void HttpUrl::Print(std::ostream& output)
{
    output << "URL: " << GetURL() << std::endl;
    output << "Protocol: " << ProtocolToString(GetProtocol()) << std::endl;
    output << "Domain: " << GetDomain() << std::endl;
    output << "Port: " << GetPort() << std::endl;
    output << "Document: " << GetDocument() << std::endl;
}