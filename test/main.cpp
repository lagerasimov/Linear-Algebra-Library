#include <linalg.h>
#include <iostream>
#include <test.h>

int main() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "Choose a test to run (0 for exit):\n";
        std::cout << "1. testDefaultConstructor\n";
        std::cout << "2. testOneParametrConstructor\n";
        std::cout << "3. testBadOneParametrConstructor\n";
        std::cout << "4. testTwoParametrsConstructor\n";
        std::cout << "5. testBadTwoParametrsConstructor\n";
        std::cout << "6. testCopyConstructor\n";
        std::cout << "7. testBadCopyConstructor\n";
        std::cout << "8. testMoveConstructor\n";
        std::cout << "9. testEqualOperator\n";
        std::cout << "10. testNonEqualOperator\n";
        std::cout << "11. testPowerWithInvert\n";
        std::cout << "12. testMatrixPlusNumber\n";
        std::cout << "13. testReshape\n";
        std::cout << "14. testDet\n";
        std::cout << "15. testBadDet1\n";
        std::cout << "16. testBadDet2\n";
        std::cout << "17. testKramer\n";
        std::cout << "18. testKramerBad1\n";
        std::cout << "19. testKramerBad2\n";
        std::cout << "20. testKramerBad3\n";
        std::cout << "21. testBadPower\n";
        std::cout << "22. testTranspose\n";
        std::cout << "23. testInitializerList\n";
        std::cout << "24. testBadInitializerList1\n";
        std::cout << "25. testBadInitializerList2\n";
        std::cout << "26. testNorm\n";
        std::cout << "27. testConcatence\n";
        std::cout << "28. testBadConcatence1\n";
        std::cout << "29. testBadConcatence2\n";
        std::cout << "30. testTrace\n";
        std::cout << "31. testBadTrace1\n";
        std::cout << "32. testBadTrace2\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "\n";

        switch (choice) {
        case 1:
            test::testDefaultConstructor();
            break;
        case 2:
            test::testOneParametrConstructor();
            break;
        case 3:
            test::testBadOneParametrConstructor();
            break;
        case 4:
            test::testTwoParametrsConstructor();
            break;
        case 5:
            test::testBadTwoParametrsConstructor();
            break;
        case 6:
            test::testCopyConstructor();
            break;
        case 7:
            test::testBadCopyConstructor();
            break;
        case 8:
            test::testMoveConstructor();
            break;
        case 9:
            test::testEqualOperator();
            break;
        case 10:
            test::testNonEqualOperator();
            break;
        case 11:
            test::testPowerWithInvert();
            break;
        case 12:
            test::testMatrixPlusNumber();
            break;
        case 13:
            test::testReshape();
            break;
        case 14:
            test::testDet();
            break;
        case 15:
            test::testBadDet1();
            break;
        case 16:
            test::testBadDet2();
            break;
        case 17:
            test::testKramer();
            break;
        case 18:
            test::testKramerBad1();
            break;
        case 19:
            test::testKramerBad2();
            break;
        case 20:
            test::testKramerBad3();
            break;
        case 21:
            test::testBadPower();
            break;
        case 22:
            test::testTranspose();
            break;
        case 23:
            test::testInitializerList();
            break;
        case 24:
            test::testBadInitializerList1();
            break;
        case 25:
            test::testBadInitializerList2();
            break;
        case 26:
            test::testNorm();
            break;
        case 27:
            test::testConcatence();
            break;
        case 28:
            test::testBadConcatence1();
            break;
        case 29:
            test::testBadConcatence2();
            break;
        case 30:
            test::testTrace();
            break;
        case 31:
            test::testBadTrace1();
            break;
        case 32:
            test::testBadTrace2();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
        std::cout << "\n";
    }
}
