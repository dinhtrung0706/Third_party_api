#include "unit_test.hpp"

bool UNIT_TEST::test_106()
{
    string name = "test_106";
    stringstream output;

    //! redirect cout ---------------------------
    streambuf *oldCout = std::cout.rdbuf(); // lưu buffer cũ
    std::cout.rdbuf(output.rdbuf());        // redirect cout → output

    //! data ------------------------------------
    Momo_API momoApi;
    momoApi.connect("abc");

    MomoAdapter momoAdapter(&momoApi, "order_123");
    RequestManager momoRequestManager(&momoAdapter);

    ConsoleObserver observer;
    momoRequestManager.attach(&observer);
    momoRequestManager.send("100.50");

    //! restore cout ----------------------------
    std::cout.rdbuf(oldCout); // khôi phục lại cout

    //! expect ----------------------------------
    string expect =
        "[Momo API] Connecting to abc\n"
        "[Momo API] Connected successfully.\n"
        "[Logger] Sending request: 100.50\n"
        "[Momo API] Creating payment of 100.5 for order: order_123\n"
        "[Observer] Sent payload: 100.50\n";

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}