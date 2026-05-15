#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define str_max_size ( sizeof( char ) *50 ) 
#define buffer_ini_size ( sizeof( int ) + sizeof( size_t ) +  str_max_size * 2 )
//str_max_size define o tamanho para 50 caracteres
//tam inicial do buff define o espaço para a opção do menu + 


void addperson  ( void** buffer ); //ponteiro pra ponteiro, pra caso precise realocar

void remperson  ( void** buffer ); //ponteiro pra ponteiro, pra caso precise realocar

void* serchp     ( void* buffer ); //procurar pessoa

void listall    ( void* buffer ); //listar todos

void menu 		( void* buffer );

void ClearStdinBuffer ();

void PrintPerson ( void* buffer );

int main () {

    void* buffer = malloc( buffer_ini_size );

        if ( !buffer ) {                       //testa se tem memoria o suficiente
            
            perror ( "Sem memória\n" );
            return 1;

        }

        memset ( buffer, 0, buffer_ini_size ); //limpa o lixo da memoria

        while ( 1 ) { //loop enquanto != 5

            int* choice = ( int* ) buffer; //deixar os paretenses, precisa pra mudar de void pra int

            if ( *choice == 5 ) {

                break;
            }

			menu ( buffer );

            switch ( *choice ) {

                case ( 1 ):
                    printf ( " 1. adicionar pessoa \n");
                    addperson ( &buffer );
                break;
            
                case ( 2 ):
                    printf ( " 2. remover pessoa \n");
                    remperson ( &buffer );
                break;

                case ( 3 ):
                    printf ( " 3. buscar por email \n");
                    PrintPerson ( buffer );
                break;

                case ( 4 ):
                    printf ( " 4. listar \n");
                    listall ( buffer );
                break;

                case ( 5 ):
                    printf ( " 5. saindo do programa \n");
                    
                break;
            }
        }

    free ( buffer );
    return 0;

}

void menu ( void* buffer ) {

    int* choice = ( int* ) buffer;

    do {

        printf( " Escolha sua opção: \n");
        printf( "1- Adicionar pessoa: \n" );
        printf( "2- Remover pessoa: \n" );
        printf( "3- Buscar pessoa: \n" );
        printf( "4- Listar todos \n" );
        printf( "5- Sair \n" );
        scanf( "%d", choice );

    }   while ( *choice < 1 || *choice > 5 );

    getchar ();

}



void ClearStdinBuffer() {
	
	while( 1 ) {
		switch( getchar() ) {
		case '\n':
		case EOF:
			return;

		}
	}

}




void addperson ( void** buffer ) {
	
	char* tempName	= ( char* )( ( char* )*buffer + sizeof( int ) + sizeof( size_t ) );
	char* tempEmail = ( char* )( tempName + str_max_size );

	printf( "Nome: " );
	scanf( " %49[^\n]", tempName );
	ClearStdinBuffer();

	printf( "Email: " );
	scanf( " %49[^\n]", tempEmail );
	ClearStdinBuffer();

	if( serchp( *buffer ) != NULL ) {
		printf( "Já existe uma pessoa com este email!" );
		memset( tempName, 0, str_max_size * 2 );
		return;
	}

	size_t* peopleDataSize = ( size_t* )( ( char* )*buffer + sizeof( int ) );
	// buffer = tamanho_fixo + tamanho_pessoas + 1 int + (nome+\0) + (email+\0)
	void* tempBuffer = realloc( *buffer, buffer_ini_size + *peopleDataSize + sizeof( int ) + ( strlen( tempName ) + 1 ) + ( strlen( tempEmail ) + 1 ) );

	if( !tempBuffer ) {
		printf( "Memória insuficiente!" );
		return;
	}

	*buffer = tempBuffer;

	peopleDataSize = ( size_t* )( ( char* )*buffer + sizeof( int ) );
	tempName	   = ( char* )( ( char* )*buffer + sizeof( int ) + sizeof( size_t ) );
	tempEmail	   = ( char* )( tempName + str_max_size );

	int*  age	= ( int* )( ( char* )*buffer + buffer_ini_size + *peopleDataSize );
	char* name	= ( char* )( ( char* )age + sizeof( int ) );
	char* email = ( char* )( name + ( ( strlen( tempName ) + 1 ) * sizeof( char ) ) );

	strcpy( name, tempName );
	strcpy( email, tempEmail );

	printf( "Idade: " );
	scanf( "%d", age );
	ClearStdinBuffer();

	*peopleDataSize += sizeof( int ) + ( strlen( tempName ) + 1 ) + ( strlen( tempEmail ) + 1 );

	memset( tempName, 0, str_max_size * 2 );
}



void remperson ( void** buffer ) {
	size_t* sizepeople = ( size_t* )( ( char* )*buffer + sizeof( int ) );
	char*	tempName	   = ( char* )( ( char* )sizepeople + sizeof( size_t ) ); 
	char*	tempEmail	   = ( char* )( tempName + str_max_size );

	printf( "\nEmail: " );
	scanf( " %49[^\n]", tempEmail );
	ClearStdinBuffer();

	void* person = serchp( *buffer );

	if( person == NULL ) {
		printf( "\nPessoa não encontrada!\n" );
		memset( tempEmail, 0, str_max_size );
		return;
	}
	char* name	= ( char* )( ( char* )person + sizeof( int ) );
	char* email = ( char* )( name + strlen( name ) + 1 );

	
	void* nextPerson = ( void* )( ( char* )email + strlen( email ) + 1 );

	
	void* peopleEnd = ( void* )( ( char* )*buffer + buffer_ini_size + *sizepeople );

	*sizepeople -= ( sizeof( int ) + ( strlen( name ) + 1 ) + ( strlen( email ) + 1 ) );

	if( nextPerson < peopleEnd ) {
		memmove( person, nextPerson, ( char* )peopleEnd - ( char* )nextPerson );
	}

	memset( tempEmail, 0, str_max_size );

	void* tempBuffer = realloc( *buffer, buffer_ini_size + *sizepeople );
	if( !tempBuffer ) {
		printf( "Memória insuficiente!" );
		return;
	}

	*buffer = tempBuffer;

	printf( "\nPessoa removida!\n" );
}



void* serchp ( void* buffer ) {
	size_t* sizepeople = ( size_t* )( ( char* )buffer + sizeof( int ) );

	if( !*sizepeople )
		return NULL;

	char* tempEmail = ( char* )( ( char* )buffer + buffer_ini_size - str_max_size );

	void* person = ( char* )buffer + buffer_ini_size;
	void* peopleEnd = ( char* )person + *sizepeople;

	while( person < peopleEnd ) {
		char* currentName  = ( char* )( ( char* )person + sizeof( int ) );
		char* currentEmail = ( char* )( currentName + strlen( currentName ) + 1 );

		if( strcmp( currentEmail, tempEmail ) == 0 )
			return person;

		person = ( void* )( ( char* )currentEmail + strlen( currentEmail ) + 1 );
	}

	return NULL;
}



void PrintPerson ( void* buffer ) {
	size_t* sizepeople = ( size_t* )( ( char* )buffer + sizeof( int ) );
	char*	tempName	   = ( char* )( ( char* )sizepeople + sizeof( size_t ) );
	char*	tempEmail	   = ( char* )( tempName + str_max_size );
	printf( "\nEmail: " );
	scanf( " %49[^\n]", tempEmail );
	ClearStdinBuffer();

	void* person = serchp( buffer );

	if( person == NULL ) {
		printf( "\nPessoa não encontrada!\n" );
		memset( tempEmail, 0, str_max_size );
		return;
	}

	int*  age	= ( int* )person;
	char* name	= ( char* )( ( char* )person + sizeof( int ) );
	char* email = ( char* )( name + strlen( name ) + 1 );

	printf( "\nNome: %s\n", name );
	printf( "Email: %s\n", email );
	printf( "Idade: %d\n", *age );

	memset( tempEmail, 0, str_max_size );
}



void listall ( void* buffer ) {
	size_t* sizepeople = ( size_t* )( ( char* )buffer + sizeof( int ) );

	if( !*sizepeople ) {
		printf( "\nNão há nenhuma pessoa na lista!\n" );
		return;
	}

	void* person = ( char* )buffer + buffer_ini_size;
	void* peopleEnd = ( char* )person + *sizepeople;

	while( person < peopleEnd ) {
		int*  age	= ( int* )person;
		char* name	= ( char* )( ( char* )person + sizeof( int ) );
		char* email = ( char* )( name + strlen( name ) + 1 );

		printf( "\nNome: %s\n", name );
		printf( "Email: %s\n", email );
		printf( "Idade: %d\n", *age );

		person = ( void* )( ( char* )email + strlen( email ) + 1 );
	}
}
