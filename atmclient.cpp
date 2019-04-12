
// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <bits/stdc++.h>
#define PORT 8080
using namespace std;
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    string hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    memset(&serv_addr, '0', sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    //send(sock , hello , strlen(hello) , 0 );
    













	string query;

	while(1){
		cin>>query;
		int num = query.length(),flag,balance;
		for(int i=0;i<num;i++) buffer[i]=query[i];
		send(sock , &num , sizeof(int) , 0 );
		send(sock , buffer , 1024 , 0 );

		cin>>query;
		num = query.length();
		for(int i=0;i<num;i++) buffer[i]=query[i];
		send(sock , &num , sizeof(int) , 0 );
		send(sock , buffer , 1024 , 0 );
		
		if(query=="exit") break;
		
		valread = read( sock , &flag , sizeof(int));
		valread = read( sock , &num , sizeof(int));
		valread = read(sock , buffer , 1024);
		query = "";
		for(int i=0;i<num;i++) query+=buffer[i];
		cout<<query<<endl;	

		if(flag==1){
			cout<<"Enter the amount to withdraw : ";
			cin>>balance;
			send(sock , &balance , sizeof(int) , 0 );

			valread = read( sock , &flag , sizeof(int));
			valread = read( sock , &num , sizeof(int));
			valread = read(sock , buffer , 1024);
			query = "";
			for(int i=0;i<num;i++) query+=buffer[i];
			cout<<query<<endl;	
		}


	}

    return 0;
}

