🧪 Mock Publisher–Broker–Subscriber Unit Test (Catch2 v3 + Protobuf + Alpine)
This project demonstrates a mock unit‑test workflow between:

a Publisher client

a NATS message broker

a Subscriber client

using a cross‑platform Protobuf data format, tested with the Catch2 v3 framework and built on the official Alpine Linux image.

The goal is to validate message flow, multi‑subscriber behavior, and protobuf serialization/deserialization in a lightweight, reproducible environment.

🛠️ Compiling Tests Manually (g++)
You can compile the test suite directly from the terminal:

```
g++ -Iinclude tests/*.cpp -o test_runners \
    -I/usr/local/include -L/usr/local/lib \
    -lCatch2Main -lCatch2
```
    
Run all tests under a tag:
```
./test_runners "[tag]"
```

Run only a specific section under a tag:
```
./test_runners "[tag]" -c "section_name"
```

**Example:**

Run all sections under the tag:
```
./test_runners "[multi_sub_receive_msg]"
```

Run only a specific section:
```
./test_runners "[multi_sub_receive_msg]" -c "Client connects successfully"
```

Another example:
```
./test_runners "[multi_sub_receive_msg]" -c "Multiple subscribers receive the same published message"
```

Screenshots
<img width="1627" height="280" alt="image" src="https://github.com/user-attachments/assets/c8a92b9a-ab36-4d50-ac79-bea7cbe9e8d4" />

<img width="850" height="237" alt="image" src="https://github.com/user-attachments/assets/3c5a2bfd-9abb-4711-b475-e1176debd62e" />

<br>
<br>
<br>


📦**Using Protobuf Data Format**

Example .proto schema:

```
syntax = "proto3";

message Telemetry {
    int32 id = 1;
    int32 temp = 2;
}
```

🐧 Alpine vs glibc: Why Linking Protobuf Is Harder on Alpine
On most Linux distributions that use glibc, linking Protobuf with Abseil is simple.
But Alpine uses musl, and Abseil depends on glibc‑specific internals such as futex.

Because musl does not provide these interfaces, Alpine maintainers must:

* patch Abseil heavily

* disable unsupported features

* split Abseil into ~130 micro‑libraries

Starting with Protobuf 4.x, Abseil became a mandatory dependency, which makes linking more complex on Alpine.

On glibc‑based systems (Ubuntu, Debian, Fedora)
You can link with just a few Abseil libraries:
```
-labsl -labsl_strings -labsl_log
```
<br>
On Alpine (musl)
You must explicitly link the micro‑libraries required by your generated Protobuf code:

```
-lprotobuf -lprotobuf-lite
-labsl_base -labsl_strings
-labsl_raw_logging_internal
-labsl_log_internal_check_op
-labsl_log_internal_message
-labsl_log_internal_nullguard
```

Example:

<img width="967" height="552" alt="image" src="https://github.com/user-attachments/assets/917bdf50-2d81-44e9-80dd-7bb3d1f205ac" />
