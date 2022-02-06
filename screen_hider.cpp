#include <windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

const string version = "0.1.0";

int main() {
    POINT xypos;
    const int sx = GetSystemMetrics(SM_CXSCREEN);  //x and y screen size
    const int sy = GetSystemMetrics(SM_CYSCREEN);


    cout << "This application comes from a GitHub project EnhancedMind/ScreenHider (https://github.com/EnhancedMind/ScreenHider).\nThe use is possible for free while keeping the credits.\nMade by EnhancedMind\nVersion " << version << "\n\n";
    
    cout << "Select time for how long the mouse must be in the corner before turning the screens off in ms (default 2000ms): ";
    
    int time = 2000;  //default value and handling of user defined value
    string timeString;
    getline( cin, timeString );
    if ( !timeString.empty() ) time = stoi(timeString);
    
    int cycles = time/350 + 1;  //calculation of delay
    int delay = time/cycles;
    if (time < 200) {
        cycles = 0;
        delay = 200;
    }

    cout << "Select how far the mouse can be in order to still turn off the screens in pixels (default 10px): ";
    
    int cpx = 10;  //default value and handling of user defined value
    string cpxString;
    getline( cin, cpxString );
    if ( !cpxString.empty() ) cpx = stoi(cpxString);


    cout << "Delay is set to " << cycles * delay << "ms and corner distance is set to " << cpx << "px." << endl;


    cout << "Detection started!" << endl;

    int cycle = 0;
	while (true) {
        GetCursorPos(&xypos);

        if (xypos.x <= cpx && xypos.y <= cpx || xypos.x >= (sx - cpx) && xypos.y <= cpx || xypos.x <= cpx && xypos.y >= (sy - cpx) || xypos.x >= (sx - cpx) && xypos.y >= (sy - cpx)) {
            if (xypos.x >= -cpx && xypos.y >= -cpx && xypos.x <= (sx + cpx) && xypos.y <= (sy + cpx)) {
                if (cycle == cycles) {
                    system("powershell (Add-Type '[DllImport(\\\"user32.dll\\\")]^public static extern int PostMessage(int hWnd, int hMsg, int wParam, int lParam);' -Name a -Pas)::PostMessage(-1,0x0112,0xF170,2)");
                    cout << "Hidden the screens!" << endl;
                }
                cycle++;
            }
        }
        else cycle = 0;

        Sleep(delay);
	}

    return 0;
}
