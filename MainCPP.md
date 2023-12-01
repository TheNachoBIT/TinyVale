# MainCPP: The Entry Point

**This is the beginning of the program**, where everything begins, and to some extent, where everything ends in TinyVale. This is where commands are handled, and big operations execute: from building and coding, to have tools that benefit the developer's experience.

## It all starts with...

...something that all C & C++ developers know what it is.

It has the usual "int main()" with the argument count and vector, and then it checks if "argc" is less than or equals to 1, it exists the program.

```c++
int main(int argc, char const *argv[])
{
	if(argc <= 1) {
		return 0;
	}

	// ...
```

As many of you may know, this is a way to check if you didn't add any parameters. Since "argv\[0\]" is the full route to TinyVale's binary/program, if that's the only element available, that means there's no input at all and its useless to continue.

Later on in the future, probably it will display a welcome message.

## If the user added arguments:

We get the first one and put it into a string.

```c++
std::string cmd = argv[1];
```

And check if "cmd" is equals to "build" or "emit".

Since 90% of both "build" and "emit" are exactly the same (process-wise), there's no need to split the functionality.

If one of them is true, then we:

- Read the "main.vale" file and put the result in "str".
  
  ```c++
  std::ifstream t("main.vale");
  std::string str((std::istreambuf_iterator<char>(t)),
  		           std::istreambuf_iterator<char>());
  ```

- Initialize the CodeGen.

  ```c++
  CodeGen::Initialize();
  ```

- Start the Lexer, by first Adding "str" to the Lexer's Content with Lexer::AddContent(), and then executing Lexer::Start().

  ```c++
  Lexer::AddContent(str);
  Lexer::Start();
  ```

- And then finally we check if it can build, by checking if ```cmd == "build"```, and Run the Parser with Parser::MainLoop(), pushing the build check into it.

  ```c++
  bool canBuild = cmd == "build";
  Parser::MainLoop(canBuild);
  ```

Then, once all of the processes are done, we finally exit the program with the classic ```return 0;```.