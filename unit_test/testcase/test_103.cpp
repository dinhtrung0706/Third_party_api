#include "unit_test.hpp"

bool UNIT_TEST::test_103()
{
    string name = "test_103";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    DeepSeek_API api;
    DeepSeekAdapter adapter(&api, "deepseek-coder");
    ConsoleObserver observer;
    RequestManager manager(&adapter);
    manager.attach(&observer);
    manager.send("Explain this C++ code.");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    std::string expect =
        "[Logger] Sending request: Explain this C++ code.\n"
        "[DeepSeek] Query: Explain this C++ code. on model: deepseek-coder\n"
        "[Observer] Sent payload: Explain this C++ code.\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}