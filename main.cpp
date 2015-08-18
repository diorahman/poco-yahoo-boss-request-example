#include <iostream>

#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/OAuth10Credentials.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

using Poco::Net::HTTPSClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::OAuth10Credentials;
using Poco::Net::Context;
using Poco::Net::HTMLForm;
using Poco::StreamCopier;
using Poco::URI;

int main(int argc, char **argv) { 
  // using `web` as provider
  URI uri("https://yboss.yahooapis.com/ysearch/web?q=cat");

  // init the creds, I think the empty token and token secret are important
  OAuth10Credentials creds(
      "dj0yJmk9eGx5RzFQOVAwcDZpJmQ9WVdrOWVVUkhWamhwTkdVbWNHbzlNQS0tJnM9Y29uc3VtZXJzZWNyZXQmeD0wYw--", 
      "2bf8a4682c4948fb4f7add9598eef5f86b57cf93", "", "");
  
  HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPathEtc());
  
  // put the `q` as param
  HTMLForm params;
  params.set("q", "cat");

  creds.authenticate(request, uri, params);
  std::string auth = request.get("Authorization");
  std::cout << auth << std::endl;

  const Context::Ptr context = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
  HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
  session.sendRequest(request);

  HTTPResponse response;
  std::istream& rs = session.receiveResponse(response);
  std::cout << response.getStatus() << " " << response.getReason() << std::endl;
  StreamCopier::copyStream(rs, std::cout);
  return 0;
}
