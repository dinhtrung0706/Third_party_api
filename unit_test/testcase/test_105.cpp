#include "unit_test.hpp"

bool UNIT_TEST::test_105()
{
    string name = "test_105";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    ChatGPT_API api;
    ChatGPTAdapter adapter(&api);
    ConsoleObserver observer;
    RequestManager manager(&adapter);
    manager.attach(&observer);
    manager.detach(&observer);

    manager.send("This should not be observed.");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    std::string expect =
        "[Logger] Sending request: This should not be observed.\n"
        "[ChatGPT] Message: This should not be observed.\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}