#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

void encodeblock( unsigned char in[3], unsigned char out[4], int len )
{
    //printf("%s ",in);
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}

void encode( FILE *infile, FILE *outfile)
{
    unsigned char in[3], out[4];
    int i, len;

    while( !feof( infile ) ) {
        len = 0;
        for( i = 0; i < 3; i++ ) {
            in[i] = (unsigned char) getc( infile );
            for (int j = 0; j < 8; j++) {
              printf("%d", !!((in[i] << j) & 0x80));
            }
            if( !feof( infile ) ) {
                len++;
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
          printf("\n");
            encodeblock( in, out, len );
            for( i = 0; i < 4; i++ ) {

                for (int j = 0; j < 8; j++) {
                  printf("%d", !!((in[i] << j) & 0x80));
                }
                putc( out[i], outfile );
            }
        }
    }
}

void decodeblock( unsigned char in[4], unsigned char out[3] )
{
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

void decode( FILE *infile, FILE *outfile )
{
    unsigned char in[4], out[3], v;
    int i, len;
    while( !feof( infile ) ) {
        for( len = 0, i = 0; i < 4 && !feof( infile ); i++ ) {
            v = 0;
            while( !feof( infile ) && v == 0 ) {
                v = (unsigned char) getc( infile );
                v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
                if( v ) {
                    v = (unsigned char) ((v == '$') ? 0 : v - 61);
                }
            }
            if( !feof( infile ) ) {
                len++;
                if( v ) {
                    in[ i ] = (unsigned char) (v - 1);
                }
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
            decodeblock( in, out );
            for( i = 0; i < len - 1; i++ ) {
                putc( out[i], outfile );
            }
        }
    }
}

int main( int argc, char const *argv[] )
{
  FILE *fr;
  FILE *fw;
  fr = fopen( "input.txt", "rb" );
  fw = fopen( "output.txt", "wb" );
  if(argc){
    if (!strcmp(argv[1],"e")){ encode(fr,fw);}
  }
  fclose(fr);
  fclose(fw);
  return 0;
}
