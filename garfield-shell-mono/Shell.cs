using System;
using System.Diagnostics;
using System.IO;

namespace garfieldshell

{
	public class Shell
	{
		String SNACKCMD = "garfield-snack";


		String user;
		String password;
		String bookinguser;
		String lastCmd;

		public Shell (String user, String password)
		{
			this.user = user;
			this.password = password;
			this.bookinguser = "";
			lastCmd = "";
		}

		public static void Main(String[] args) {

			//parse args
                        //TODO

                        Console.Write ("We need a user:");
                        String user = Console.ReadLine ();
                        Console.WriteLine ("We need a password:");
                        Shell shell = new Shell (user, "");

                        shell.askPassword ();

                        shell.shell ();

		}



		public void shell() {

			while(true) {
				Console.Write (user + ">");

				parse (getInput());
			}

		}

		private String getInput() {

			String input = "";
			ConsoleKeyInfo key;


			while ((key = Console.ReadKey()).Key != ConsoleKey.Enter) {
				if (key.Key == ConsoleKey.UpArrow) {
					input = lastCmd;
					clearLine ();
					Console.Write (user + ">");
					Console.Write (lastCmd);
				} else if (key.Key == ConsoleKey.Backspace) {

					if (input.Length > 0) {
						input = input.Remove (input.Length - 1);
					} else {
						Console.Write (">");
					}
				} else {
					input += key.KeyChar;
				}
			}
			Console.WriteLine ("debug: " + input);
			return input;
		}

		private void clearLine() {
			Console.SetCursorPosition(0, Console.CursorTop);
			Console.Write(new string(' ', Console.WindowWidth));
			Console.SetCursorPosition(0, Console.CursorTop);
		}


		private void parse(String input) {
			lastCmd = input;

			if (input.StartsWith("exit")) {
				Environment.Exit (0);
			}


			if (input.StartsWith ("buy ")) {


				input = input.Remove (0, 4);
				String[] inputs = input.Split (' ');
				foreach (String s in inputs) {
					int output;
					if (int.TryParse(s, out output)) {
						buy(output);
					} else {
						buy(s);
					}
				}
				return;
			}

			if (input.StartsWith ("find ")) {
				find (input.Remove (0, 5));
				return;
			}

			if (input.StartsWith ("set user ")) {
				input = input.Remove (0, 9);
				bookinguser = input;
				return;
			}

			if (input.StartsWith ("info ")) {
				info(input.Remove(0, 5));
				return;
			}


			Console.WriteLine ("Command not found!");
		}

		private void info(String snack) {
			String args = "--user " + user + " info " + snack;
			exec (SNACKCMD, args);
		}

		private void buy(String buy) {
			String args;
			if (bookinguser != "") {
				args = "--user " + user + " buy -u " + bookinguser + " -s " + buy;
			} else {
				args = "--user " + user + " buy -s " + buy;
			}
			exec (SNACKCMD, args);
		}

		private void buy(int id) {
			String args;
			if (bookinguser != "") {
				args = "--user " + user + " buy -u " + bookinguser + " " + id;
			} else {
				args = "--user " + user + " buy " + id;
			}

			exec (SNACKCMD, args);
		}

		private void find(String search) {
			String args = "--user " + user + " find " + search;
			exec (SNACKCMD, args);
		}

		private void exec (String cmd, String args) {
			Process snack = new Process ();
			snack.StartInfo.FileName = cmd;
			snack.StartInfo.Arguments = args;
			snack.StartInfo.UseShellExecute = false;
			snack.StartInfo.RedirectStandardInput = true;
			snack.StartInfo.RedirectStandardOutput = true;
			snack.Start ();

			StreamWriter writer = snack.StandardInput;
			StreamReader reader = snack.StandardOutput;
			writer.WriteLine (password);
			writer.Flush ();
			writer.Close ();


			Console.Write(reader.ReadToEnd ());
			snack.WaitForExit ();
			reader.Close ();
		}

		public void askPassword() {

			ConsoleKeyInfo key;
			String pass = "";

			while ((key = Console.ReadKey(true)).Key != ConsoleKey.Enter) {
				if (key.Key != ConsoleKey.Backspace)
				{
					pass += key.KeyChar;
				}
				else
				{
					if (key.Key == ConsoleKey.Backspace && pass.Length > 0)
					{
						pass = pass.Substring(0, (pass.Length - 1));
					}
				}
			}

			password = pass;
		}
	}
}

