#include "unit_test.hpp"

bool UNIT_TEST::test_101()
{
    string name = "test_101";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    ChatGPT_API gptApi;
    ChatGPTAdapter gptAdapter(&gptApi);
    ConsoleObserver observer;
    RequestManager gptManager(&gptAdapter);
    gptManager.attach(&observer);
    gptManager.send("What is the weather today?");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    string expect =
        "[Logger] Sending request: What is the weather today?\n"
        "[ChatGPT] Message: What is the weather today?\n"
        "[Observer] Sent payload: What is the weather today?\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}