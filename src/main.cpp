#include <iostream>
#include <crow.h>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <chrono>
#include <random>
#include <crow/middlewares/session.h>
#include <crow/middlewares/cookie_parser.h>

using Session = crow::SessionMiddleware<crow::FileStore>;

// returns timestamp of first user entrance
std::string generateCookie()
{
	auto now = fmt::localtime(std::time(nullptr));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> dist(1, 10000);
	return fmt::format("date: {:%Y-%m-%d} time: {:%H:%M:%S} --- {}", now, now, dist(rng));
}

std::string readFile(const std::string& path) 
{
	std::ifstream file(path, std::ios::binary);
	if (!file) return "";
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main(int argc, char** argv)
{
	crow::App<crow::CookieParser, Session> app{ Session{
		crow::FileStore{"tmp/sessiondata"}
	}};

	CROW_ROUTE(app, "/")([&](crow::request request) {
		if (request.method == crow::HTTPMethod::Get)
		{
			std::cout << "Get\n";
		}

		auto& ctx = app.get_context<crow::CookieParser>(request);

		if (ctx.get_cookie("key") == "")
		{
			ctx.set_cookie("key", generateCookie())
				.path("/")
				.max_age(120);
		}		
		
		std::string mainPage = crow::mustache::load_text("index.html");
		mainPage.append(ctx.get_cookie("key"));
		return mainPage;
	});

	CROW_ROUTE(app, "/static/<string>")([](const std::string& filename) {

		std::string script = readFile("static/" + filename);
		crow::response response(script);

		if (filename.rfind(".js") != std::string::npos)
		{
			response.set_header("Content-Type", "application/javascript");
		}
		else if (filename.rfind(".css") != std::string::npos)
		{
			response.set_header("Content-Type", "text/css");
		}

		return response;
	});

	app.port(5559).multithreaded().run();

	return 0;
}
