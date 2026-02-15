//------------------------------------------------------------------------------
//  FileHeader.cs 
//  Copyright (c) EndoraSoft.  All rights reserved.
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using Microsoft.VisualStudio.Shell;
using EnvDTE;
using System.IO;

namespace Remarks
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class FileHeaderGEN
    {
        string author = "";
        string enterprise = "";

        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0102;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("f1afa488-901c-4e32-968e-37155ebb3d2e");

        /// <summary>
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly Package package;

        /// <summary>
        /// Initializes a new instance of the <see cref="FileHeader"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        private FileHeaderGEN(Package package)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (package == null)
            {
                throw new ArgumentNullException("package");
            }

            this.package = package;

            OleMenuCommandService commandService = this.ServiceProvider.GetService(typeof(IMenuCommandService)) as OleMenuCommandService;
            if (commandService != null)
            {
                var menuCommandID = new CommandID(CommandSet, CommandId);
                var menuItem = new MenuCommand(this.MenuItemCallback, menuCommandID);
                commandService.AddCommand(menuItem);
                             
                try
                {                   
                    DTE dte = (DTE)ServiceProvider.GetService(typeof(DTE));
                    string userfoldername = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);

                    using (StreamReader sr = new StreamReader(userfoldername + "\\MacrosAuthor.txt"))
                    {
                        String line = sr.ReadToEnd();
                        string[] array = line.Split('\n');
                        author = array[0].Replace('\r', ' ');
                        enterprise = array[1].Replace('\r', ' ');
                    }
                }
                catch (Exception)
                {
                    author = "No se ha podido abrir el fichero de author";
                }
            }
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static FileHeaderGEN Instance
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the service provider from the owner package.
        /// </summary>
        private IServiceProvider ServiceProvider
        {
            get
            {
                return this.package;
            }
        }

        /// <summary>
        /// Initializes the singleton instance of the command.
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        public static void Initialize(Package package)
        {
            Instance = new FileHeaderGEN(package);
        }

        /// <summary>
        /// This function is the callback used to execute the command when the menu item is clicked.
        /// See the constructor to see how the menu item is associated with this function using
        /// OleMenuCommandService service and MenuCommand class.
        /// </summary>
        /// <param name="sender">Event sender.</param>
        /// <param name="e">Event args.</param>
        private void MenuItemCallback(object sender, EventArgs e)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            DTE dte = (DTE)ServiceProvider.GetService(typeof(DTE));
            if (dte == null) return;

            if (dte.ActiveDocument != null)
            {
                dte.ActiveDocument.Save();
                var  dtename    = dte.ActiveDocument.FullName;
                var  ext        = Path.GetExtension(dtename);
                var  name       = Path.GetFileName(dtename);
                var  group      = "";
                bool isGEN      = false;
                bool isUnitTest = false;

                string directory = "";

                directory = Path.GetDirectoryName(dtename);

                GetGroupID(directory, ref isGEN, ref isUnitTest, ref group);

                if((ext == ".cpp") || (ext == ".c"))
                  {
                    ProcessCPPHeader(dte, isGEN, name, group);
                  }

                if(ext == ".hpp" || ext == ".h")
                  {
                    int size = ext.Length;
                    ext = ext.Substring(1, (size - 1));

                    ProcessHHeader(dte, isGEN, name, ext, group);
                  }
            }
        }

        private void GetGroupID(string directory, ref bool isGEN, ref bool isUnitTest, ref string groupID)
        {
          isUnitTest = false;
          isGEN = false;

          groupID = "";

          // is GEN?
          if ((directory.Contains("/GEN/")) ||
              (directory.Contains("\\GEN\\")) ||
              (directory.Contains("/GENFrameWork/")) ||
              (directory.Contains("\\GENFrameWork\\"))) isGEN = true;

          if (isGEN)
          {
            // Types
            if (directory.Contains("AppFlow")) groupID = "APPFLOW";
            if (directory.Contains("Cipher")) groupID = "CIPHER";
            if (directory.Contains("Common")) groupID = "COMMON";
            if (directory.Contains("Compress")) groupID = "COMPRESS";
            if (directory.Contains("Databases")) groupID = "DATABASE";
            if (directory.Contains("DataIO")) groupID = "DATAIO";
            if (directory.Contains("Graphic")) groupID = "GRAPHIC";
            if (directory.Contains("Identification")) groupID = "IDENTIFICATION";
            if (directory.Contains("Input")) groupID = "INPUT";
            if (directory.Contains("MainProc")) groupID = "MAIN_PROCEDURE";
            if (directory.Contains("Script")) groupID = "SCRIPT";
            if (directory.Contains("Sound")) groupID = "SOUND";
            if (directory.Contains("UserInterface")) groupID = "USERINTERFACE";
            if (directory.Contains("XUtils")) groupID = "XUTILS";

            if (directory.Contains("Examples")) groupID = "EXAMPLES";
            if (directory.Contains("Tests")) groupID = "TESTS";
            if (directory.Contains("UnitTests"))
            {
              isUnitTest = true;
              groupID = "UNIT_TEST";
            }

            // Platforms
            if (directory.Contains("Windows")) groupID = "PLATFORM_WINDOWS";
            if (directory.Contains("Linux")) groupID = "PLATFORM_LINUX";
            if (directory.Contains("Android")) groupID = "PLATFORM_ANDROID";
            if (directory.Contains("Common")) groupID = "PLATFORM_COMMON";
            if (directory.Contains("STM32")) groupID = "PLATFORM_STM32";
            if (directory.Contains("ESP32")) groupID = "PLATFORM_ESP32";
            if (directory.Contains("SAMD5xE5x")) groupID = "PLATFORM_SAMD5XE5X";

            if (groupID.Length == 0)
            {
              groupID = "APPLICATION";
            }
          }
        }

        private void CreateInfo(bool isGEN, string name, string description, string group, ref string info)
        {
            string date           = DateTime.Now.ToString();
            var    namewithoutext = Path.GetFileNameWithoutExtension(name);

            info  = "\n";
            info += "@file       " + name + "\n";
            info += "\n";
            info += "@class      " + (namewithoutext.ToUpper()) + "\n";
            info += "@brief      " + description + "\n";
            info += "@ingroup    " + group + "\n";
            info += "\n";
            if(isGEN == false )
              { 
                info += "@author     " + author + "\n";
                info += "@date       " + date + "\n";
                info += "\n";
              }
        }

        private void CreateCopyright(bool isGEN,  ref string copyright)
        {
            if(isGEN)
              {
                copyright  =  "@copyright  " + "GEN Group." + " All rights reserved.\n";
                copyright += "\n";
                copyright += "@cond\n";
                copyright += "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated\n";
                copyright += "documentation files(the \"Software\"), to deal in the Software without restriction, including without limitation\n";
                copyright += "the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,\n";
                copyright += "and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n";
                copyright += "\n";
                copyright += "The above copyright notice and this permission notice shall be included in all copies or substantial portions of\n";
                copyright += "the Software.\n";
                copyright += "\n";
                copyright += "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO\n";
                copyright += "THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\n";
                copyright += "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,\n";
                copyright += "TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n";
                copyright += "SOFTWARE.\n";
                copyright += "@endcond\n";
                copyright += "\n";
             }
            else
             {
                copyright  = "@copyright  " + enterprise + ". All rights reserved.\n";
                copyright += "\n";
             }
        }

        private void ProcessCPPHeader(DTE dte, bool isGEN, string name, string group)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            var    selection        = (TextSelection)dte.ActiveDocument.Selection;
            string text             = selection.Text;
            var    namewithoutext   = Path.GetFileNameWithoutExtension(name);
            string info             = "";
            string copyright        = "";
            string description      = Microsoft.VisualBasic.Interaction.InputBox(   "Purpose of the file"   ,
                                                                                    "File module C, CPP"    ,
                                                                                    "");

            selection.GotoLine(1, true);

            // Replace the selection with the modified text.

            selection.Text += "/**-------------------------------------------------------------------------------------------------------------------\n";

            CreateInfo(isGEN, name, description, group, ref info);
            selection.Text += info;

            CreateCopyright(isGEN, ref copyright);
            selection.Text += copyright;

            selection.Text += "--------------------------------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n";

            selection.Text += "/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n";
            selection.Text += "#include \"GEN_Defines.h\"\n";
            selection.Text += "\n\n";
            
            selection.Text += "/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n";
            selection.Text += "#include \"" + namewithoutext + ".h\"\n";
            selection.Text += "\n\n";

            selection.Text += "/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n";
            selection.Text += "#include \"GEN_Control.h\"\n";
            selection.Text += "\n\n";

            selection.Text += "/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n\n";
            
            selection.Text += "/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/\n";            
            selection.Text += "\n";
            selection.Text += namewithoutext.ToUpper() + "::" + namewithoutext.ToUpper() + "()\n";
            selection.Text += "{\n";
            selection.Text += "  Clean();\n";
            selection.Text += "}\n";
            selection.Text += "\n\n";
            selection.Text += namewithoutext.ToUpper() + "::~" + namewithoutext.ToUpper() + "()\n";
            selection.Text += "{\n";
            selection.Text += "  Clean();\n";
            selection.Text += "}\n";
            selection.Text += "\n\n";
            selection.Text += "void " + namewithoutext.ToUpper() + "::Clean()\n";
            selection.Text += "{\n";
            selection.Text += "}\n";
            selection.Text += "\n\n";
    }

    private void ProcessHHeader(DTE dte, bool isGEN, string name, string ext, string group)
    {
            ThreadHelper.ThrowIfNotOnUIThread();

            var     selection       = (TextSelection)dte.ActiveDocument.Selection;
            string  text            = selection.Text;
            var     namewithoutext  = Path.GetFileNameWithoutExtension(name);
            string  info            = "";
            string  copyright       = "";
            string  description     = Microsoft.VisualBasic.Interaction.InputBox( "Purpose of the file"   ,
                                                                                  "File header H,HPP"    ,
                                                                                  "");

            selection.GotoLine(1, true);

            // Replace the selection with the modified text.

            selection.Text += "/**-------------------------------------------------------------------------------------------------------------------\n";

            CreateInfo(isGEN, name, description, group, ref info);
            selection.Text += info;

            CreateCopyright(isGEN, ref copyright);
            selection.Text += copyright;

            selection.Text += "--------------------------------------------------------------------------------------------------------------------*/\n";
            selection.Text += "#pragma once\n";
            selection.Text += "\n";              

            selection.Text += "/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n\n";       
            
            selection.Text += "/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n\n";
            
            selection.Text += "/*---- CLASS ---------------------------------------------------------------------------------------------------------*/\n";
            selection.Text += "\n";
            selection.Text += "class " + namewithoutext.ToUpper() + "\n";
            selection.Text += "{\n";
            selection.Text += "  public:\n";
            selection.Text += "                    " + namewithoutext.ToUpper() + "    ();\n";
            selection.Text += "    virtual        ~" + namewithoutext.ToUpper() + "    ();\n";
            selection.Text += "\n";
            selection.Text += "  protected:\n";
            selection.Text += "\n";
            selection.Text += "  private:\n";
            selection.Text += "\n";
            selection.Text += "    void            Clean    ();\n";
            selection.Text += "};";           
            selection.Text += "\n\n";
            
            selection.Text += "/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/\n";                   
            selection.Text += "\n\n";
        }
    }
}
