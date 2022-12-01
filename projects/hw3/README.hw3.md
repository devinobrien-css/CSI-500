# HW3 Sockets and Ports

## Objective
Create a server to accept multiple requests from a client

### Agenda
- [ ] Server
    * accepts multiple requests from client 
    * serverDecoder
        - [x] read in from socket,
        - [ ] decode messages
        - [ ] create 7 threads: 
            * charA
                - [ ] replace all a's with capital A's
                - [ ] share recieved data with charE in queueA2E
                - [ ] terminate
            * charE
                - [ ] replace all e's with capital E's
                - [ ] share recieved data with charI in queueE2I
                - [ ] terminate
            * charI
                - [ ] replace all i's with capital I's
                - [ ] share recieved data with charO in queueO2U
                - [ ] terminate
            * charO
                - [ ] replace all o's with capital O's
                - [ ] share recieved data with charU in queueO2U
                - [ ] terminate
            * charU
                - [ ] replace all u's with capital U's
                - [ ] share recieved data with digit in queueU2D
                - [ ] terminate
            * digit
                - [ ] compute sum of all digits found in data
                - [ ] append sum to end of buffer in format: 
                    `Sum of digits is %d`
                - [ ] share recieved data with digit in queueD2W
                - [ ] terminate
            * writer
                - [ ] share final buffer with serverEncoder
                - [ ] terminate
    * serverEncoder
        - [ ] encode resulting data
        - [ ]

- [ ] Client
    - [ ] encode and send request to server
    - [ ] recieve and decode response from server