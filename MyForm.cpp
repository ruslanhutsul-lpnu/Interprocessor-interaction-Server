//#include "MyForm.h"
//using namespace System;
//using namespace System::Windows::Forms;
//
//[System::STAThread]
//int main(array<String^>^ args) {
//	Application::SetCompatibleTextRenderingDefault(false);
//	Application::EnableVisualStyles();
//	WFtry2::MyForm form;
//	Application::Run(% form);
//}

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    WFtry2::MyForm form;
    Application::Run(% form);
}
