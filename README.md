This is a mock unit test btwn Publisher client, message-broker (nats_server), and Subscriber client using Catch2 v3 Unit Test framework with Alpine official 
Hub Image.

I like to compile it directly at the terminal with g++ compiler
e.g g++ -Iinclude tests/*.cpp -o test_runners -I/usr/local/include -L/usr/local/lib -lCatch2Main -lCatch2

./test_runner "[tag]"
./test_runner "[tag]" -c "section_name"

e.g:

./test_runners "[multi_sub_receive_msg]" <-- this will execute all sections under a test case tag named "[multi_sub_receive_msg]"

./test_runners "[multi_sub_receive_msg]" -c "Client connects successfully" <-- this will only execute section named "Client connects successfully" under the test case tag named "[multi_sub_receive_msg]"  

./test_runners "[multi_sub_receive_msg]" -c "Multiple subscribers receive the same published message

<img width="1627" height="280" alt="image" src="https://github.com/user-attachments/assets/c8a92b9a-ab36-4d50-ac79-bea7cbe9e8d4" />
<img width="850" height="237" alt="image" src="https://github.com/user-attachments/assets/3c5a2bfd-9abb-4711-b475-e1176debd62e" />

