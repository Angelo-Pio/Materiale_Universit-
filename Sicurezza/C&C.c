int main(int argc, char const *argv[])
{
    /* Accept connections from bots

        accept
        receive info and save them in active_bots;
        send close message
        close connection
    */    

    /* Save bot info: 
        -> typedef struct{
            ip_address add;
            int[] ports ;
            actie_bots *next;
        }active_bots;
    
    */
    
    /*
    
        Send commands: SYS_INFO, EMAIL, HTTP_REQ -> UDP?

        using udp to send command, 

    */ 

    // List active bots with info about: target and command -> command: LIST


    return 0;
}
