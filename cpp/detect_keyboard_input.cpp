#include <stdio.h>
#include <conio.h>

int escapeCharacter = 27;

int main ()
{
    int ch;
    while ((ch = _getch()) != escapeCharacter)
    {
        printf("%d", ch);
        if (ch == 0 || ch == 224)
            printf(", %d", _getch());
        printf("\n");
    }

    printf("ESC %d\n", ch);

    return (0);
}
