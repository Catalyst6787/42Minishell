FIN:

- **fix leaks**
- handle errors

**Erreurs a corriger:**

echo hello'world' 
mini output = (hello'world')
bash output = (helloworld)

echo "$" 
mini output = ()
bash output = ($)

echo $?HELLO 
mini output = ()
bash output = (0HELLO)

echo > file hello
cat < file1 file2

