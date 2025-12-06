//------------------------------------------------------------------------------
//  FunctionGEN.cs 
//  Copyright (c) EndoraSoft.  All rights reserved.
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using System.Globalization;
using Microsoft.VisualStudio.Shell;
using EnvDTE;
using System.IO;
using System.Text;

namespace Remarks
{
    /// <summary>
    /// Command handler
    /// </summary>
    internal sealed class FunctionGEN
    {
        string author     = "";
        string enterprise = "";

        /// <summary>
        /// Command ID.
        /// </summary>
        public const int CommandId = 0x0100;

        /// <summary>
        /// Command menu group (command set GUID).
        /// </summary>
        public static readonly Guid CommandSet = new Guid("f1afa488-901c-4e32-968e-37155ebb3d2e");

        /// <summary>
        /// VS Package that provides this command, not null.
        /// </summary>
        private readonly Package package;

        /// <summary>
        /// Initializes a new instance of the <see cref="FunctionGEN"/> class.
        /// Adds our command handlers for menu (commands must exist in the command table file)
        /// </summary>
        /// <param name="package">Owner package, not null.</param>
        private FunctionGEN(Package package)
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

                

                DTE dte = (DTE)ServiceProvider.GetService(typeof(DTE));
                string userfoldername = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);

                try
                {

                    using (StreamReader sr = new StreamReader(userfoldername + "\\MacrosAuthor.txt"))
                    {
                        String line = sr.ReadToEnd();
                        string[] array = line.Split('\n');
                        author      = array[0].Replace('\r', ' ');
                        enterprise  = array[1].Replace('\r', ' ');
                    }
                }
                catch (Exception)
                {
                    author = Microsoft.VisualBasic.Interaction.InputBox(
                        "Names",
                        "Author name",
                        "");

                    if (author.Length == 0)
                        return;

                    enterprise = Microsoft.VisualBasic.Interaction.InputBox(
                        "Names",
                        "Enterprise name",
                        "");

                    if (enterprise.Length == 0)
                        return;

                    using (StreamWriter sw = new StreamWriter(userfoldername + "\\MacrosAuthor.txt"))
                    {
                        sw.WriteLine(author);
                        sw.WriteLine(enterprise);
                        sw.Close();
                    }

                }
            }
        }

        /// <summary>
        /// Gets the instance of the command.
        /// </summary>
        public static FunctionGEN Instance
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
            Instance = new FunctionGEN(package);
        }

        private void GetGroupID(string directory, ref bool isGEN, ref bool isUnitTest, ref string groupID)
        {
            isUnitTest  = false;
            isGEN       = false;

            groupID = "";

            // is GEN?
            if ((directory.Contains("/GEN/"))          ||
                (directory.Contains("\\GEN\\"))        ||
                (directory.Contains("/GENFrameWork/")) ||
                (directory.Contains("\\GENFrameWork\\"))) isGEN = true;

            if(isGEN)
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

        static string TransformString(string input)
        {
          if (string.IsNullOrEmpty(input)) return input;

          StringBuilder output = new StringBuilder();
          bool inUpperCaseGroup = false;

          for (int i = 0; i < input.Length; i++)
          {
            char current = input[i];

            if (current == '_')
            {
              if (i > 0) // Replace '_' with space unless it's the first character
              {
                output.Append(' ');
              }
            }
            else if (char.IsUpper(current))
            {
              if (!inUpperCaseGroup) // Start of a new uppercase group
              {
                if (output.Length > 0) // Add a space before the group if not the start
                {
                  output.Append(' ');
                }
                inUpperCaseGroup = true;
              }

              // Add the uppercase character as is (to determine if it's a single char later)
              output.Append(current);
            }
            else
            {
              // Non-uppercase character ends any active uppercase group
              if (inUpperCaseGroup)
              {
                // Convert the previous uppercase group to the proper format
                FormatUpperCaseGroup(output);
                inUpperCaseGroup = false;
              }

              output.Append(current);
            }
          }

          // Handle a trailing uppercase group
          if (inUpperCaseGroup)
          {
            FormatUpperCaseGroup(output);
          }

          // If the first character is a space, remove it
          if (output.Length > 0 && output[0] == ' ')
          {
            output.Remove(0, 1);
          }

          return output.ToString();
        }


        private static void FormatUpperCaseGroup(StringBuilder output)
        {
          int startIndex = output.Length - 1;

          // Find the start of the uppercase group
          while (startIndex >= 0 && char.IsUpper(output[startIndex]))
          {
            startIndex--;
          }

          startIndex++; // Adjust to the first uppercase character

          int length = output.Length - startIndex;

          if (length == 1) // Single uppercase character
          {
            char singleChar = char.ToLower(output[startIndex]);
            output[startIndex] = singleChar;
          }
          else // Uppercase group
          {
            // Insert space before the last uppercase character and convert it to lowercase
            char lastChar = char.ToLower(output[output.Length - 1]);
            output[output.Length - 1] = lastChar;
          }
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

            if(dte.ActiveDocument != null)
              {
                var       selection     = (TextSelection)dte.ActiveDocument.Selection;
                string    text          = selection.Text;

                string    funcname      = "";
                string    description   = "";

                string    version       = "";
                string    returntype    = "";

                string[]  parameters    = null;

                DateTime  localDate     = DateTime.Now;
                var       culture       = new CultureInfo("es-ES");

                bool      isvirtual     = false;
                bool      isinternal    = false;
                bool      consanddes    = false;  

                version = localDate.ToString(culture);

                if(text.Length==0) return;

                //------------ eliminamos tabs y espacios

                string line = text.Replace("\t", " ");
                while (line.IndexOf(" *") > 0)
                  {
                    line = line.Replace(" *", "*");
                  }

                while(line.IndexOf("  ") > 0)
                  {
                    line = line.Replace("  ", " ");
                  }


                text = line.TrimEnd(' ');

                if(text.Length == 0) return;

                //------------ buscamos el return type y el contexto
                int parenthesis = text.IndexOf('(');
                int parenthesis2 = text.IndexOf(')');
                int space = text.IndexOf(' ');
                int i;             
                if((space == -1) || (parenthesis < space)) //no tiene return type (constructor/destructor)
                  {
                    returntype = "";

                    consanddes = true;

                    if(text.IndexOf('~') == -1)
                      {
                        description = "Constructor of class";                          
                      }
                     else
                      {
                        description = "Destructor of class";
                        isvirtual = true;
                       }

                    if(parenthesis < 0) return;

                    if(parenthesis >= parenthesis2) return;

                    funcname = text.Substring(0, parenthesis);
                    parameters = text.Substring(parenthesis + 1, parenthesis2 - parenthesis - 1).Split(',');

                    for (i = 0; i < parameters.Length; i++)
                      {
                        parameters[i] = parameters[i].Trim();

                        int size = parameters[i].Length;
                        int pos = parameters[i].IndexOf(' ');

                        if (pos != -1)
                          {
                            if (size > pos + 1)
                              {
                                parameters[i] = parameters[i].Substring(pos + 1, (size - (pos + 1)));
                              }
                          }
                      }
                  }

                if((space != -1) && (parenthesis > space))
                  {
                    description = Microsoft.VisualBasic.Interaction.InputBox( "Purpose of this function"  ,
                                                                              "Function of file"          ,
                                                                              "");

                    returntype = text.Substring(0, space);
                    funcname   = text.Substring(space, parenthesis-space);

                    parameters = text.Substring(parenthesis + 1, parenthesis2 - parenthesis-1).Split(',');

                    for(i=0; i<parameters.Length; i++)
                       {
                         parameters[i] = parameters[i].Trim();

                         int size = parameters[i].Length;
                         int pos = parameters[i].IndexOf(' ');

                         if(pos != -1)
                           {
                             if(size > pos + 1)
                               {
                                 parameters[i] = parameters[i].Substring(pos + 1, (size-(pos+1)));
                               }
                           }
                     }
                  }

                var     dtename     = dte.ActiveDocument.FullName;
                string  date        = DateTime.Now.ToString();
                string  directory   = "";
                bool    isGEN       = false;
                bool    isUnitTest  = false;
                string  group       = "";

                directory = Path.GetDirectoryName(dtename);

                GetGroupID(directory, ref isGEN, ref isUnitTest, ref group);

                string   result;

                if(((funcname.Contains("::Clean")) && (description.Length == 0)))
                  {
                    isinternal  = true;
                    description = "Clean the attributes of the class: Default initialize";
                  }

                if(((funcname.Contains("::HandleEvent")) && (description.Length == 0)))
                  {
                    isinternal  = true;
                    description = "Handle Event for the observer manager of this class";
                  }

                if(description.Length == 0)
                  {
                    description = funcname.Trim();

                    // It´s a classe member
                    int index2points = description.IndexOf(':');
                    if(index2points !=0)
                      {
                        description = description.Substring(index2points + 2);
                        description = TransformString(description);
                      }
                  }

                result  = "/**-------------------------------------------------------------------------------------------------------------------\n";
                result += "\n";

                if(isUnitTest)
                  {
                    result += "@fn \t\t\t\t"    + text        + "\n";
                    result += "@brief\t\t\t"    + "Unit test of " + parameters[0] + ": " + parameters[1] + "\n"; 
                    result += "@ingroup\t\t"    + group       + "\n";
                    if(isinternal)  result += "@note\t\t\t\tINTERNAL\n";
                    if(isvirtual)   result += "@note\t\t\t\tVIRTUAL\n";                   
                    //result += "\n";
                    //result += "@author \t\t"    + author      + "\n";
                    //result += "@date\t\t\t\t"   + date        + "\n";  
                  }
                 else
                  { 
                    result += "@fn \t\t\t\t"    + text        + "\n";
                    result += "@brief\t\t\t"    + description + "\n";
                    result += "@ingroup\t\t"    + group       + "\n";
                    if(isinternal)  result += "@note\t\t\t\tINTERNAL\n";
                    if(isvirtual)   result += "@note\t\t\t\tVIRTUAL\n";
                    
                    //result += "\n";
                    //result += "@author \t\t"    + author      + "\n";
                    //result += "@date\t\t\t\t"   + date        + "\n";

                    if(parameters != null)
                      {
                        if(parameters.Length != 0)
                          {
                            if(parameters[0].Length != 0)
                              {
                                result += "\n";

                                for(i = 0; i < parameters.Length; i++)
                                  {
                                    // Default use param["in"] because is it is more likely

                                    if(parameters[i].Length != 0) result += "@param[in]\t" + parameters[i] + " : \n";

                                  }
                              }
                          }
                      }
                  }  
                
                result += "\n";

                if(returntype.Length == 0)
                  {
                    // result += "@return\t\t\t" +"Does not return anything. \n";
                  }
                 else
                  {
                    if(returntype == "void")
                      {
                        // result += "@return\t\t\t" + returntype + " : does not return anything. \n";
                      }
                      else
                      {
                        if(returntype == "bool")
                          {
                            result += "@return\t\t\t" + returntype + " : true if is succesful. \n";
                            result += "\n";
            }
                          else
                          {
                            result += "@return\t\t\t" + returntype + " : \n";
                            result += "\n";
                          }
                      }
                  }
                                           
                result += "--------------------------------------------------------------------------------------------------------------------*/\n";
                result += selection.Text;
                selection.Text = result;                
            }
        }
    }
}
