#include "cmdline.hpp"
#include "sessions.hpp"
#include "ioutil.hpp"

int main(int argc, const char *const *argv)
{

    tucker::cli::init();
    tucker::cli::parse(argc, argv);

    std::string hostname, username, password;
    tucker::cli::getHostname(hostname);
    tucker::cli::getPassword(password);
    tucker::cli::getUsername(username);

    if (username == OPTSTR_NOT_SET) {
        std::cout << "Enter Username: ";
        std::cin >> username;
        tucker::ioutil::getChar(); // grab RETURN slip.
    }

    if (password == OPTSTR_NOT_SET)
        password = tucker::ioutil::getPassword("Enter Password: ", 42);

    tucker::JSessionID jid(hostname, username, password);
    std::cout << jid << std::endl;

    return 0;
}
