**Interactive address book manager**

------------------------------------------------------------------------------------

Quickstart guide:
1. Start the program.
2. Type "help" and press enter to see all available commands.

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
compile - creates only the object files.  <br/>
address_book - same as all.  <br/>
clean - removes all creates files.  <br/>
