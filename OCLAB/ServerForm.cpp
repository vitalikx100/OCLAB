#include "ServerForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ arg)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    OCLAB::ServerForm form; //WinFormsTest - ��� ������ �������
    Application::Run(% form);
  
}


