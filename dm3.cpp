

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

using namespace std;

const int MAX = 50;

int domainA[MAX], codomainB[MAX];
int mapping[MAX];
int domainSize = 0, codomainSize = 0;

int domainA2[MAX], codomainB2[MAX];
int mapping2[MAX];
int domainSize2, codomainSize2;

int screenWidth, screenHeight;
int centerX;
int contentStartX;

void getconsolemeasures(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void print_colored(char symbol, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << symbol;
    SetConsoleTextAttribute(hConsole, 7);
}

void print_colored_text(string text, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << text;
    SetConsoleTextAttribute(hConsole, 7);
}

void printAt(int y, string text, int indent = 0, int color = 7)
{
    gotoxy(contentStartX + indent, y);
    print_colored_text(text, color);
}

void printXY(int x, int y, string text, int color = 7)
{
    gotoxy(x, y);
    print_colored_text(text, color);
}

void hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}

void showCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(h, &info);
}

void draw_boundary()
{
    getconsolemeasures(screenWidth, screenHeight);
    centerX = screenWidth / 2;
    contentStartX = (screenWidth - 60) / 2;

    gotoxy(0, 0);
    for (int i = 0; i < screenWidth; i++)
        print_colored('=', 11);

    gotoxy(0, screenHeight - 1);
    for (int i = 0; i < screenWidth; i++)
        print_colored('=', 11);

    for (int y = 1; y < screenHeight - 1; y++)
    {
        gotoxy(0, y);
        print_colored('|', 11);
        gotoxy(screenWidth - 1, y);
        print_colored('|', 11);
    }
}

void header()
{
    int boxWidth = 60;
    int startX = (screenWidth - boxWidth) / 2;

    gotoxy(startX, 2);
    print_colored_text("+", 14);
    for (int i = 0; i < boxWidth - 2; i++)
        print_colored_text("=", 14);
    print_colored_text("+", 14);

    gotoxy(startX, 3);
    print_colored_text("|", 14);
    string title1 = "DISCRETE MATHEMATICS PROJECT";
    gotoxy(startX + (boxWidth - title1.length()) / 2, 3);
    print_colored_text(title1, 15);
    gotoxy(startX + boxWidth - 1, 3);
    print_colored_text("|", 14);

    gotoxy(startX, 4);
    print_colored_text("|", 14);
    string title2 = "Function Properties Checker";
    gotoxy(startX + (boxWidth - title2.length()) / 2, 4);
    print_colored_text(title2, 10);
    gotoxy(startX + boxWidth - 1, 4);
    print_colored_text("|", 14);

    gotoxy(startX, 5);
    print_colored_text("+", 14);
    for (int i = 0; i < boxWidth - 2; i++)
        print_colored_text("=", 14);
    print_colored_text("+", 14);
}

void clearScreen()
{
    system("cls");
    hideCursor();
    draw_boundary();
    header();
}

void clearinsideboundary()
{
    for (int y = 7; y < screenHeight - 1; y++)
    {
        gotoxy(2, y);
        for (int x = 2; x < screenWidth - 2; x++)
            cout << ' ';
    }
}

void pause()
{
    gotoxy(contentStartX, screenHeight - 3);
    print_colored_text(">>> Press any key to continue... <<<", 14);
    _getch();
}

void drawLine(int y, int width = 60, int color = 11)
{
    gotoxy(contentStartX, y);
    for (int i = 0; i < width; i++)
        print_colored('-', color);
}

void drawDoubleLine(int y, int width = 60, int color = 14)
{
    gotoxy(contentStartX, y);
    for (int i = 0; i < width; i++)
        print_colored('=', color);
}

void printSectionHeader(int y, string title, int color = 15)
{
    int padding = (60 - title.length()) / 2;
    gotoxy(contentStartX, y);
    for (int i = 0; i < 60; i++)
        print_colored('=', 14);

    gotoxy(contentStartX + padding, y + 1);
    print_colored_text(title, color);

    gotoxy(contentStartX, y + 2);
    for (int i = 0; i < 60; i++)
        print_colored('=', 14);
}

void showMenu()
{
    clearinsideboundary();

    printSectionHeader(8, "MAIN MENU");

    int y = 12;

    printAt(y, "  [1]  Enter a new function", 0, 7);
    printAt(y + 1, "  [2]  Display the function", 0, 7);
    printAt(y + 2, "  [3]  Check if Injective (One-to-One)", 0, 7);
    printAt(y + 3, "  [4]  Check if Surjective (Onto)", 0, 7);
    printAt(y + 4, "  [5]  Check if Bijective", 0, 7);
    printAt(y + 5, "  [6]  Find Inverse Function", 0, 7);
    printAt(y + 6, "  [7]  Composition of Functions", 0, 7);
    printAt(y + 7, "  [8]  Check All Properties", 0, 7);
    printAt(y + 8, "  [9]  Run Example Demo", 0, 7);
    printAt(y + 9, "  [10] Exit", 0, 7);

    drawLine(y + 11);

    gotoxy(contentStartX, y + 13);
    print_colored_text("  Enter your choice: ", 14);
}

int isInCodomain(int value)
{
    for (int i = 0; i < codomainSize; i++)
    {
        if (codomainB[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

int isInCodomain2(int value)
{
    for (int i = 0; i < codomainSize2; i++)
    {
        if (codomainB2[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

void displayDomainCodomainSummary(int y)
{
    gotoxy(contentStartX, y);
    print_colored_text("Domain A   = { ", 14);
    for (int i = 0; i < domainSize; i++)
    {
        cout << domainA[i];
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, y + 1);
    print_colored_text("Codomain B = { ", 14);
    for (int i = 0; i < codomainSize; i++)
    {
        cout << codomainB[i];
        if (i < codomainSize - 1)
            cout << ", ";
    }
    cout << " }";
}

void inputFunction()
{
    clearinsideboundary();
    printSectionHeader(8, "DEFINE NEW FUNCTION f: A -> B");

    int y = 12;

    printAt(y, "Enter number of elements in Domain A: ", 0, 10);
    showCursor();
    cin >> domainSize;
    hideCursor();

    printAt(y + 2, "Enter elements of Domain A:", 0, 14);
    drawLine(y + 3, 30);

    for (int i = 0; i < domainSize; i++)
    {
        gotoxy(contentStartX + 2, y + 4 + i);
        cout << "Element [" << i + 1 << "]: ";
        showCursor();
        cin >> domainA[i];
        hideCursor();
    }

    int codomainY = y + 5 + domainSize;
    printAt(codomainY, "Enter number of elements in Codomain B: ", 0, 10);
    showCursor();
    cin >> codomainSize;
    hideCursor();

    printAt(codomainY + 2, "Enter elements of Codomain B:", 0, 14);
    drawLine(codomainY + 3, 30);

    for (int i = 0; i < codomainSize; i++)
    {
        gotoxy(contentStartX + 2, codomainY + 4 + i);
        cout << "Element [" << i + 1 << "]: ";
        showCursor();
        cin >> codomainB[i];
        hideCursor();
    }

    pause();

    clearinsideboundary();
    printSectionHeader(8, "DEFINE FUNCTION MAPPINGS");

    // Show domain and codomain summary
    displayDomainCodomainSummary(12);

    drawLine(14);

    y = 16;
    printAt(y, "Define f: A -> B (map each domain element):", 0, 10);
    drawLine(y + 1, 45);

    for (int i = 0; i < domainSize; i++)
    {
        int valid = 0;
        while (valid == 0)
        {
            gotoxy(contentStartX + 2, y + 2 + i);
            cout << "f(" << domainA[i] << ") = ";
            showCursor();
            cin >> mapping[i];
            hideCursor();

            if (isInCodomain(mapping[i]))
            {
                valid = 1;

                gotoxy(contentStartX + 25, y + 2 + i);
                cout << "                              ";
            }
            else
            {
                gotoxy(contentStartX + 25, y + 2 + i);
                print_colored_text("[Error: Not in codomain!]", 12);
                gotoxy(contentStartX + 2, y + 2 + i);
                cout << "                    ";
            }
        }
    }

    drawLine(y + 3 + domainSize);
    printAt(y + 4 + domainSize, "Function defined successfully!", 0, 10);

    pause();
    clearinsideboundary();
}

void displayFunction()
{
    clearinsideboundary();
    printSectionHeader(8, "FUNCTION DETAILS");

    int y = 12;

    gotoxy(contentStartX, y);
    print_colored_text("Domain A   = { ", 14);
    for (int i = 0; i < domainSize; i++)
    {
        cout << domainA[i];
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, y + 1);
    print_colored_text("Codomain B = { ", 14);
    for (int i = 0; i < codomainSize; i++)
    {
        cout << codomainB[i];
        if (i < codomainSize - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(y + 3);

    gotoxy(contentStartX, y + 5);
    print_colored_text("Function f = { ", 10);
    for (int i = 0; i < domainSize; i++)
    {
        cout << "(" << domainA[i] << "," << mapping[i] << ")";
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(y + 7);

    printAt(y + 9, "Mappings:", 0, 14);
    for (int i = 0; i < domainSize; i++)
    {
        gotoxy(contentStartX + 2, y + 10 + i);
        cout << "f(" << domainA[i] << ") = " << mapping[i];
    }

    int range[MAX];
    int rangeSize = 0;

    for (int i = 0; i < domainSize; i++)
    {
        int found = 0;
        for (int j = 0; j < rangeSize; j++)
        {
            if (range[j] == mapping[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            range[rangeSize] = mapping[i];
            rangeSize++;
        }
    }

    drawLine(y + 11 + domainSize);

    gotoxy(contentStartX, y + 13 + domainSize);
    print_colored_text("Range      = { ", 11);
    for (int i = 0; i < rangeSize; i++)
    {
        cout << range[i];
        if (i < rangeSize - 1)
            cout << ", ";
    }
    cout << " }";

    pause();
    clearinsideboundary();
}

int checkInjective()
{
    clearinsideboundary();
    printSectionHeader(8, "CHECKING INJECTIVE (ONE-TO-ONE)");

    int y = 12;

    printAt(y, "Definition:", 0, 14);
    printAt(y + 1, "A function is injective if no two different", 2, 7);
    printAt(y + 2, "domain elements map to the same value.", 2, 7);
    printAt(y + 3, "i.e., f(a) = f(b) implies a = b", 2, 7);

    drawLine(y + 5);

    int isInjective = 1;
    int violationY = y + 7;

    for (int i = 0; i < domainSize; i++)
    {
        for (int j = i + 1; j < domainSize; j++)
        {
            if (mapping[i] == mapping[j])
            {
                printAt(violationY, "VIOLATION FOUND!", 0, 12);
                gotoxy(contentStartX + 2, violationY + 1);
                cout << "f(" << domainA[i] << ") = " << mapping[i];
                gotoxy(contentStartX + 2, violationY + 2);
                cout << "f(" << domainA[j] << ") = " << mapping[j];
                gotoxy(contentStartX + 2, violationY + 3);
                cout << "Both " << domainA[i] << " and " << domainA[j] << " map to " << mapping[i];
                violationY += 5;
                isInjective = 0;
            }
        }
    }

    drawLine(violationY);

    if (isInjective == 1)
    {
        printAt(violationY + 2, "RESULT: The function IS INJECTIVE", 0, 10);
        printAt(violationY + 3, "Each domain element maps to a unique value.", 2, 7);
    }
    else
    {
        printAt(violationY + 2, "RESULT: The function is NOT INJECTIVE", 0, 12);
        printAt(violationY + 3, "Multiple domain elements map to same value.", 2, 7);
    }

    pause();
    clearinsideboundary();
    return isInjective;
}

int checkSurjective()
{
    clearinsideboundary();
    printSectionHeader(8, "CHECKING SURJECTIVE (ONTO)");

    int y = 12;

    printAt(y, "Definition:", 0, 14);
    printAt(y + 1, "A function is surjective if every element", 2, 7);
    printAt(y + 2, "in the codomain is mapped to by some element.", 2, 7);
    printAt(y + 3, "i.e., Range = Codomain", 2, 7);

    drawLine(y + 5);

    int isSurjective = 1;
    int unmapped[MAX];
    int unmappedCount = 0;

    for (int i = 0; i < codomainSize; i++)
    {
        int found = 0;
        for (int j = 0; j < domainSize; j++)
        {
            if (mapping[j] == codomainB[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            unmapped[unmappedCount] = codomainB[i];
            unmappedCount++;
            isSurjective = 0;
        }
    }

    int resultY = y + 7;

    if (isSurjective == 0)
    {
        printAt(resultY, "VIOLATION FOUND!", 0, 12);
        printAt(resultY + 1, "Unmapped codomain elements:", 2, 7);
        gotoxy(contentStartX + 4, resultY + 2);
        cout << "{ ";
        for (int i = 0; i < unmappedCount; i++)
        {
            cout << unmapped[i];
            if (i < unmappedCount - 1)
                cout << ", ";
        }
        cout << " }";
        resultY += 4;
    }

    drawLine(resultY);

    if (isSurjective == 1)
    {
        printAt(resultY + 2, "RESULT: The function IS SURJECTIVE", 0, 10);
        printAt(resultY + 3, "Every codomain element has pre-image.", 2, 7);
    }
    else
    {
        printAt(resultY + 2, "RESULT: The function is NOT SURJECTIVE", 0, 12);
        printAt(resultY + 3, "Some codomain elements are not reached.", 2, 7);
    }

    pause();
    clearinsideboundary();
    return isSurjective;
}

int checkBijective()
{
    clearinsideboundary();
    printSectionHeader(8, "CHECKING BIJECTIVE PROPERTY");

    int y = 12;

    printAt(y, "Definition:", 0, 14);
    printAt(y + 1, "A function is bijective if it is BOTH", 2, 7);
    printAt(y + 2, "injective AND surjective.", 2, 7);

    drawLine(y + 4);

    int isInjective = 1;
    for (int i = 0; i < domainSize; i++)
    {
        for (int j = i + 1; j < domainSize; j++)
        {
            if (mapping[i] == mapping[j])
            {
                isInjective = 0;
            }
        }
    }

    int isSurjective = 1;
    for (int i = 0; i < codomainSize; i++)
    {
        int found = 0;
        for (int j = 0; j < domainSize; j++)
        {
            if (mapping[j] == codomainB[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            isSurjective = 0;
        }
    }

    printAt(y + 6, "Analysis:", 0, 14);

    gotoxy(contentStartX + 2, y + 7);
    cout << "Injective:  ";
    if (isInjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO", 12);

    gotoxy(contentStartX + 2, y + 8);
    cout << "Surjective: ";
    if (isSurjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO", 12);

    drawLine(y + 10);

    if (isInjective && isSurjective)
    {
        printAt(y + 12, "RESULT: The function IS BIJECTIVE", 0, 10);
        printAt(y + 13, "It has a one-to-one correspondence.", 2, 7);
        printAt(y + 14, "An inverse function EXISTS.", 2, 10);
        pause();
        clearinsideboundary();
        return 1;
    }
    else
    {
        printAt(y + 12, "RESULT: The function is NOT BIJECTIVE", 0, 12);
        if (!isInjective && !isSurjective)
        {
            printAt(y + 13, "It is neither injective nor surjective.", 2, 7);
        }
        else if (!isInjective)
        {
            printAt(y + 13, "It fails the injective property.", 2, 7);
        }
        else
        {
            printAt(y + 13, "It fails the surjective property.", 2, 7);
        }
        printAt(y + 14, "An inverse function DOES NOT exist.", 2, 12);
        pause();
        clearinsideboundary();
        return 0;
    }
}

void findInverse()
{
    clearinsideboundary();
    printSectionHeader(8, "FINDING INVERSE FUNCTION");

    int y = 12;

    // Check if bijective first
    int isInjective = 1;
    for (int i = 0; i < domainSize; i++)
    {
        for (int j = i + 1; j < domainSize; j++)
        {
            if (mapping[i] == mapping[j])
            {
                isInjective = 0;
            }
        }
    }

    int isSurjective = 1;
    for (int i = 0; i < codomainSize; i++)
    {
        int found = 0;
        for (int j = 0; j < domainSize; j++)
        {
            if (mapping[j] == codomainB[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            isSurjective = 0;
        }
    }

    printAt(y, "Checking prerequisites:", 0, 14);

    gotoxy(contentStartX + 2, y + 1);
    cout << "Injective:  ";
    if (isInjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO", 12);

    gotoxy(contentStartX + 2, y + 2);
    cout << "Surjective: ";
    if (isSurjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO", 12);

    drawLine(y + 4);

    if (!isInjective || !isSurjective)
    {
        printAt(y + 6, "INVERSE DOES NOT EXIST!", 0, 12);
        printAt(y + 7, "The function must be bijective for inverse.", 2, 7);
        pause();
        clearinsideboundary();
        return;
    }

    printAt(y + 6, "INVERSE EXISTS!", 0, 10);

    drawLine(y + 8);

    int inverseDomain[MAX];
    int inverseMapping[MAX];
    int inverseSize = 0;

    for (int i = 0; i < domainSize; i++)
    {
        inverseDomain[i] = mapping[i];
        inverseMapping[i] = domainA[i];
        inverseSize++;
    }

    printAt(y + 10, "Original function f:", 0, 14);
    gotoxy(contentStartX + 2, y + 11);
    cout << "f = { ";
    for (int i = 0; i < domainSize; i++)
    {
        cout << "(" << domainA[i] << "," << mapping[i] << ")";
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    printAt(y + 13, "Inverse function f^(-1):", 0, 10);
    gotoxy(contentStartX + 2, y + 14);
    cout << "f^(-1) = { ";
    for (int i = 0; i < inverseSize; i++)
    {
        cout << "(" << inverseDomain[i] << "," << inverseMapping[i] << ")";
        if (i < inverseSize - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(y + 16);

    printAt(y + 18, "Inverse Mappings:", 0, 14);
    for (int i = 0; i < inverseSize; i++)
    {
        gotoxy(contentStartX + 2, y + 19 + i);
        cout << "f^(-1)(" << inverseDomain[i] << ") = " << inverseMapping[i];
    }

    int verifyY = y + 20 + inverseSize;
    drawLine(verifyY);

    printAt(verifyY + 2, "Verification: f^(-1)(f(x)) = x", 0, 11);
    for (int i = 0; i < domainSize; i++)
    {
        int x = domainA[i];
        int fx = mapping[i];

        int invfx = -1;
        for (int j = 0; j < inverseSize; j++)
        {
            if (inverseDomain[j] == fx)
            {
                invfx = inverseMapping[j];
                break;
            }
        }

        gotoxy(contentStartX + 2, verifyY + 3 + i);
        cout << "f^(-1)(f(" << x << ")) = f^(-1)(" << fx << ") = " << invfx << " ";
        if (invfx == x)
        {
            print_colored_text("[OK]", 10);
        }
        else
        {
            print_colored_text("[FAIL]", 12);
        }
    }

    pause();
    clearinsideboundary();
}

void inputSecondFunction()
{
    clearinsideboundary();
    printSectionHeader(8, "DEFINE SECOND FUNCTION g: C -> D");

    int y = 12;

    printAt(y, "Enter number of elements in Domain C: ", 0, 10);
    showCursor();
    cin >> domainSize2;
    hideCursor();

    printAt(y + 2, "Enter elements of Domain C:", 0, 14);
    for (int i = 0; i < domainSize2; i++)
    {
        gotoxy(contentStartX + 2, y + 3 + i);
        cout << "Element [" << i + 1 << "]: ";
        showCursor();
        cin >> domainA2[i];
        hideCursor();
    }

    int codomainY = y + 4 + domainSize2;
    printAt(codomainY, "Enter number of elements in Codomain D: ", 0, 10);
    showCursor();
    cin >> codomainSize2;
    hideCursor();

    printAt(codomainY + 2, "Enter elements of Codomain D:", 0, 14);
    for (int i = 0; i < codomainSize2; i++)
    {
        gotoxy(contentStartX + 2, codomainY + 3 + i);
        cout << "Element [" << i + 1 << "]: ";
        showCursor();
        cin >> codomainB2[i];
        hideCursor();
    }

    pause();

    clearinsideboundary();
    printSectionHeader(8, "DEFINE MAPPINGS FOR g");

    gotoxy(contentStartX, 12);
    print_colored_text("Domain C   = { ", 14);
    for (int i = 0; i < domainSize2; i++)
    {
        cout << domainA2[i];
        if (i < domainSize2 - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, 13);
    print_colored_text("Codomain D = { ", 14);
    for (int i = 0; i < codomainSize2; i++)
    {
        cout << codomainB2[i];
        if (i < codomainSize2 - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(15);

    printAt(17, "Define g: C -> D:", 0, 10);

    for (int i = 0; i < domainSize2; i++)
    {
        int valid = 0;
        while (valid == 0)
        {
            gotoxy(contentStartX + 2, 18 + i);
            cout << "g(" << domainA2[i] << ") = ";
            showCursor();
            cin >> mapping2[i];
            hideCursor();

            if (isInCodomain2(mapping2[i]))
            {
                valid = 1;
                gotoxy(contentStartX + 25, 18 + i);
                cout << "                        ";
            }
            else
            {
                gotoxy(contentStartX + 25, 18 + i);
                print_colored_text("[Error: Not in codomain!]", 12);
                gotoxy(contentStartX + 2, 18 + i);
                cout << "                    ";
            }
        }
    }

    drawLine(19 + domainSize2);
    printAt(20 + domainSize2, "Function g defined successfully!", 0, 10);
    pause();
}

void composeFunctions()
{
    clearinsideboundary();
    printSectionHeader(8, "COMPOSITION OF FUNCTIONS");

    int y = 12;

    if (domainSize == 0)
    {
        printAt(y, "Please define the first function (f) first!", 0, 12);
        pause();
        clearinsideboundary();
        return;
    }

    printAt(y, "We will compute (f o g)(x) = f(g(x))", 0, 7);
    printAt(y + 1, "First, we need function g (inner function)", 0, 7);

    pause();
    inputSecondFunction();

    clearinsideboundary();
    printSectionHeader(8, "COMPUTING COMPOSITION (f o g)");

    y = 12;

    gotoxy(contentStartX, y);
    print_colored_text("f = { ", 14);
    for (int i = 0; i < domainSize; i++)
    {
        cout << "(" << domainA[i] << "," << mapping[i] << ")";
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, y + 1);
    print_colored_text("g = { ", 14);
    for (int i = 0; i < domainSize2; i++)
    {
        cout << "(" << domainA2[i] << "," << mapping2[i] << ")";
        if (i < domainSize2 - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(y + 3);

    int valid = 1;
    int checkY = y + 5;

    for (int i = 0; i < domainSize2; i++)
    {
        int gx = mapping2[i];
        int found = 0;
        for (int j = 0; j < domainSize; j++)
        {
            if (domainA[j] == gx)
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            gotoxy(contentStartX, checkY);
            print_colored_text("Warning: ", 12);
            cout << "g(" << domainA2[i] << ") = " << gx << " not in domain of f!";
            checkY++;
            valid = 0;
        }
    }

    if (valid == 0)
    {
        drawLine(checkY + 1);
        printAt(checkY + 3, "Composition is INVALID!", 0, 12);
        printAt(checkY + 4, "Range of g must be subset of domain of f.", 2, 7);
        pause();
        clearinsideboundary();
        return;
    }

    printAt(y + 5, "Step-by-step computation:", 0, 10);

    int compDomain[MAX];
    int compMapping[MAX];
    int compSize = 0;

    for (int i = 0; i < domainSize2; i++)
    {
        int x = domainA2[i];
        int gx = mapping2[i];

        int fgx = -1;
        for (int j = 0; j < domainSize; j++)
        {
            if (domainA[j] == gx)
            {
                fgx = mapping[j];
                break;
            }
        }

        gotoxy(contentStartX + 2, y + 7 + i);
        cout << "(f o g)(" << x << ") = f(g(" << x << ")) = f(" << gx << ") = " << fgx;

        compDomain[compSize] = x;
        compMapping[compSize] = fgx;
        compSize++;
    }

    drawLine(y + 8 + domainSize2);

    gotoxy(contentStartX, y + 10 + domainSize2);
    print_colored_text("Result: (f o g) = { ", 10);
    for (int i = 0; i < compSize; i++)
    {
        cout << "(" << compDomain[i] << "," << compMapping[i] << ")";
        if (i < compSize - 1)
            cout << ", ";
    }
    cout << " }";

    pause();
    clearinsideboundary();
}

void checkAllProperties()
{
    if (domainSize == 0)
    {
        clearinsideboundary();
        printAt(15, "Please define a function first!", 0, 12);
        pause();
        clearinsideboundary();
        return;
    }

    clearinsideboundary();
    printSectionHeader(8, "COMPLETE FUNCTION ANALYSIS");

    int y = 12;

    gotoxy(contentStartX, y);
    print_colored_text("Domain A   = { ", 14);
    for (int i = 0; i < domainSize; i++)
    {
        cout << domainA[i];
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, y + 1);
    print_colored_text("Codomain B = { ", 14);
    for (int i = 0; i < codomainSize; i++)
    {
        cout << codomainB[i];
        if (i < codomainSize - 1)
            cout << ", ";
    }
    cout << " }";

    gotoxy(contentStartX, y + 2);
    print_colored_text("Function f = { ", 10);
    for (int i = 0; i < domainSize; i++)
    {
        cout << "(" << domainA[i] << "," << mapping[i] << ")";
        if (i < domainSize - 1)
            cout << ", ";
    }
    cout << " }";

    drawLine(y + 4);

    int isInjective = 1;
    for (int i = 0; i < domainSize; i++)
    {
        for (int j = i + 1; j < domainSize; j++)
        {
            if (mapping[i] == mapping[j])
            {
                isInjective = 0;
            }
        }
    }

    int isSurjective = 1;
    for (int i = 0; i < codomainSize; i++)
    {
        int found = 0;
        for (int j = 0; j < domainSize; j++)
        {
            if (mapping[j] == codomainB[i])
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            isSurjective = 0;
        }
    }

    int isBijective = isInjective && isSurjective;

    printAt(y + 6, "PROPERTY SUMMARY", 0, 15);
    printAt(y + 7, "+----------------------+----------+", 0, 11);
    printAt(y + 8, "| Property             |  Status  |", 0, 11);
    printAt(y + 9, "+----------------------+----------+", 0, 11);

    gotoxy(contentStartX, y + 10);
    cout << "| Injective            |   ";
    if (isInjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO ", 12);
    cout << "    |";

    gotoxy(contentStartX, y + 11);
    cout << "| Surjective           |   ";
    if (isSurjective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO ", 12);
    cout << "    |";

    gotoxy(contentStartX, y + 12);
    cout << "| Bijective            |   ";
    if (isBijective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO ", 12);
    cout << "    |";

    gotoxy(contentStartX, y + 13);
    cout << "| Inverse Exists       |   ";
    if (isBijective)
        print_colored_text("YES", 10);
    else
        print_colored_text("NO ", 12);
    cout << "    |";

    printAt(y + 14, "+----------------------+----------+", 0, 11);

    drawLine(y + 16);

    int rangeSize = 0;
    for (int i = 0; i < domainSize; i++)
    {
        int alreadyCounted = 0;
        for (int j = 0; j < i; j++)
        {
            if (mapping[j] == mapping[i])
            {
                alreadyCounted = 1;
                break;
            }
        }
        if (!alreadyCounted)
            rangeSize++;
    }

    printAt(y + 18, "CARDINALITY", 0, 14);
    gotoxy(contentStartX + 2, y + 19);
    cout << "|Domain|   = " << domainSize;
    gotoxy(contentStartX + 2, y + 20);
    cout << "|Codomain| = " << codomainSize;
    gotoxy(contentStartX + 2, y + 21);
    cout << "|Range|    = " << rangeSize;

    pause();
    clearinsideboundary();
}

void runDemo()
{
    clearinsideboundary();
    printSectionHeader(8, "EXAMPLE DEMONSTRATIONS");

    int y = 12;

    printAt(y, "  [1]  Injective but NOT Surjective", 0, 7);
    printAt(y + 1, "  [2]  Surjective but NOT Injective", 0, 7);
    printAt(y + 2, "  [3]  Bijective (both properties)", 0, 7);
    printAt(y + 3, "  [4]  Neither Injective nor Surjective", 0, 7);

    drawLine(y + 5);

    gotoxy(contentStartX, y + 7);
    print_colored_text("  Enter choice: ", 14);

    int demoChoice;
    showCursor();
    cin >> demoChoice;
    hideCursor();

    switch (demoChoice)
    {
    case 1:
        clearinsideboundary();
        printAt(12, "Loading: Injective but NOT Surjective", 0, 11);

        domainSize = 3;
        domainA[0] = 1;
        domainA[1] = 2;
        domainA[2] = 3;

        codomainSize = 4;
        codomainB[0] = 4;
        codomainB[1] = 5;
        codomainB[2] = 6;
        codomainB[3] = 7;

        mapping[0] = 4;
        mapping[1] = 5;
        mapping[2] = 6;

        pause();
        checkAllProperties();
        break;

    case 2:
        clearinsideboundary();
        printAt(12, "Loading: Surjective but NOT Injective", 0, 11);

        domainSize = 4;
        domainA[0] = 1;
        domainA[1] = 2;
        domainA[2] = 3;
        domainA[3] = 4;

        codomainSize = 3;
        codomainB[0] = 5;
        codomainB[1] = 6;
        codomainB[2] = 7;

        mapping[0] = 5;
        mapping[1] = 5;
        mapping[2] = 6;
        mapping[3] = 7;

        pause();
        checkAllProperties();
        break;

    case 3:
        clearinsideboundary();
        printAt(12, "Loading: Bijective Function", 0, 11);

        domainSize = 3;
        domainA[0] = 1;
        domainA[1] = 2;
        domainA[2] = 3;

        codomainSize = 3;
        codomainB[0] = 4;
        codomainB[1] = 5;
        codomainB[2] = 6;

        mapping[0] = 5;
        mapping[1] = 4;
        mapping[2] = 6;

        pause();
        checkAllProperties();
        findInverse();
        break;

    case 4:
        clearinsideboundary();
        printAt(12, "Loading: Neither Injective nor Surjective", 0, 11);

        domainSize = 3;
        domainA[0] = 1;
        domainA[1] = 2;
        domainA[2] = 3;

        codomainSize = 4;
        codomainB[0] = 4;
        codomainB[1] = 5;
        codomainB[2] = 6;
        codomainB[3] = 7;

        mapping[0] = 4;
        mapping[1] = 4;
        mapping[2] = 5;

        pause();
        checkAllProperties();
        break;

    default:
        printAt(y + 9, "Invalid choice!", 0, 12);
        pause();
        clearinsideboundary();
    }
}

void mainheader()
{
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(55, 10);
    cout << "Developed By: Muhammad Bilal Arshad & Ali Sher" << endl;
    gotoxy(30, 17);
    cout << " ███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗                                     " << endl;
    gotoxy(30, 18);
    cout << " ██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║                                     " << endl;
    gotoxy(30, 19);
    cout << " █████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║                                     " << endl;
    gotoxy(30, 20);
    cout << " ██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║                                     " << endl;
    gotoxy(30, 21);
    cout << " ██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║                                     " << endl;
    gotoxy(30, 22);
    cout << " ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝                                     " << endl;
    gotoxy(30, 23);
    cout << "                                                                                                        " << endl;
    gotoxy(30, 24);
    cout << "            ██████╗ ██████╗  ██████╗ ██████╗ ███████╗██████╗ ████████╗██╗███████╗███████╗               " << endl;
    gotoxy(30, 25);
    cout << "            ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔══██╗╚══██╔══╝██║██╔════╝██╔════╝               " << endl;
    gotoxy(30, 26);
    cout << "            ██████╔╝██████╔╝██║   ██║██████╔╝█████╗  ██████╔╝   ██║   ██║█████╗  ███████╗               " << endl;
    gotoxy(30, 27);
    cout << "            ██╔═══╝ ██╔══██╗██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗   ██║   ██║██╔══╝  ╚════██║               " << endl;
    gotoxy(30, 28);
    cout << "            ██║     ██║  ██║╚██████╔╝██║     ███████╗██║  ██║   ██║   ██║███████╗███████║               " << endl;
    gotoxy(30, 29);
    cout << "            ╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝╚══════╝╚══════╝               " << endl;
    gotoxy(30, 30);
    cout << "                                                                                                        " << endl;
    gotoxy(30, 31);
    cout << "                                                 ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ " << endl;
    gotoxy(30, 32);
    cout << "                                                ██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗" << endl;
    gotoxy(30, 33);
    cout << "                                                ██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝" << endl;
    gotoxy(30, 34);
    cout << "                                                ██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗" << endl;
    gotoxy(30, 35);
    cout << "                                                ╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║" << endl;
    gotoxy(30, 36);
    cout << "                                                 ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝" << endl;

    gotoxy(50, 40);
    cout << "Press any key to continue.." << endl;
    getch();
}

int main()
{
    system("cls");
    mainheader();

    clearScreen();

    int choice;

    do
    {
        showMenu();
        showCursor();
        cin >> choice;
        hideCursor();

        switch (choice)
        {
        case 1:
            inputFunction();
            break;

        case 2:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define a function first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                displayFunction();
            }
            break;

        case 3:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define a function first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                checkInjective();
            }
            break;

        case 4:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define a function first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                checkSurjective();
            }
            break;

        case 5:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define a function first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                checkBijective();
            }
            break;

        case 6:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define a function first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                findInverse();
            }
            break;

        case 7:
            if (domainSize == 0)
            {
                clearinsideboundary();
                printAt(15, "Please define function f first!", 0, 12);
                pause();
                clearinsideboundary();
            }
            else
            {
                composeFunctions();
            }
            break;

        case 8:
            checkAllProperties();
            break;

        case 9:
            runDemo();
            break;

        case 10:
            clearinsideboundary();
            drawDoubleLine(18);
            printAt(20, "Thank you for using Function Properties Checker!", 0, 10);
            printAt(22, "Goodbye!", 0, 14);
            drawDoubleLine(24);
            pause();
            break;

        default:
            clearinsideboundary();
            printAt(15, "Invalid choice! Please enter 1-10.", 0, 12);
            pause();
            clearinsideboundary();
        }

    } while (choice != 10);

    return 0;
}
