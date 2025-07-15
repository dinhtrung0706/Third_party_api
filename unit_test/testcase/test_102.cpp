#include "unit_test.hpp"

bool UNIT_TEST::test_102()
{
    string name = "test_102";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    DeepSeek_API api;
    DeepSeekAdapter adapter(&api); // default is "deepseek-chat"
    ConsoleObserver observer;
    RequestManager manager(&adapter);
    manager.attach(&observer);
    manager.send("Summarize the paragraph.");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    std::string expect =
        "[Logger] Sending request: Summarize the paragraph.\n"
        "[DeepSeek] Query: Summarize the paragraph. on model: deepseek-chat\n"
        "[Observer] Sent payload: Summarize the paragraph.\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}