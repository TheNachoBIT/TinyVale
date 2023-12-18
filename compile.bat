@echo off
setlocal enableDelayedExpansion
for /f %%i in ('where which') do set WhichPath=%%i

set BasePath=%WhichPath:\usr\bin\which.exe=\mingw64\bin%
set ClangPath=%BasePath%\clang++
set LLVMConfigPath=%BasePath%\llvm-config

set LLVMConfigResult=

%LLVMConfigPath% --cxxflags --link-static --ldflags --system-libs --libs all > llvmconfig.txt
for /f "delims=" %%x in (llvmconfig.txt) do set LLVMConfigResult=!LLVMConfigResult! %%x

echo Compiling Tiny Vale on Windows...
%ClangPath% -g -O3 language/Lexer/*.cpp language/Parser/*.cpp language/CodeGen/*.cpp language/BorrowChecker/*.cpp language/AST/*.cpp *.cpp %LLVMConfigResult% -fstack-protector -lssp -frtti -std=c++20 -static -o tinyvale

IF "%ERRORLEVEL%"=="0" (
    echo Tiny Vale Compiled Successfully
) ELSE (
    echo Tiny Vale Compilation Failed...
)

PAUSE