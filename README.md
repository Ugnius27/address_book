**Interactive address book manager**

------------------------------------------------------------------------------------

Quickstart guide:
1. Run the "make" command in the project's root directory.
2. Start the program.
3. Type "help" and press enter to see all available commands.
4. (Optional) Run "sudo make install" for a permanent installation.

------------------------------------------------------------------------------------

All commands

1. list
2. append \<entry>
3. insert \<index> \<entry>
4. delete \<index>|all
5. find \<index>|name \<name>|surname \<surname>|email \<email>|number \<number>
6. help
7. exit

\<entry> = name,surname,email,number

Note: Commands, arguments and address entries are case and whitespace sensitive.
------------------------------------------------------------------------------------

Example commands: <br/>
append Ugnius,Stasaitis,pastas@p.lt,+123456789 <br/>
insert 5 Petras,Petrenas,petras@p.lt,321 <br/>
find 3 <br/>
find name Ugnius <br/>
find surname Petrenas <br/>
list <br/>
delete 2 <br/>
delete all <br/>

------------------------------------------------------------------------------------

**Make targets:**

all - builds the entire project.  <br/>
compile - creates only the src directory object files.  <br/>
address_book - same as all.  <br/>
clean - removes all created files.  <br/>
install - permanently installs the program into /usr/local/bin. The required linked_list libraries are installed into /usr/local/lib and /usr/local/include.
uninstall - removes all files created by install.
