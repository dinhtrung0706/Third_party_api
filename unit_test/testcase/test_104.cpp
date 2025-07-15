#include "unit_test.hpp"

bool UNIT_TEST::test_104()
{
    string name = "test_104";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    DeepSeek_API api;
    DeepSeekAdapter adapter(&api, "deepseek-chat");
    ConsoleObserver observer;
    RequestManager manager(&adapter);
    manager.attach(&observer);
    manager.attach(&observer);
    manager.send("Is this duplicated?");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    std::string expect =
        "[Logger] Sending request: Is this duplicated?\n"
        "[DeepSeek] Query: Is this duplicated? on model: deepseek-chat\n"
        "[Observer] Sent payload: Is this duplicated?\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
