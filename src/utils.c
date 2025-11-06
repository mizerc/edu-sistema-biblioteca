#include "types.h"

// OS - TERMINAL
void os_limparTela(void)
{
#ifdef _WIN32
	os_system("cls");
#endif
#ifdef _MACOS
	os_system("clear");
#endif
}
void printBorder(int n) {
    putchar('+');
    for (int i = 0; i < n+1; i++) {
        putchar('-');
    }
}
void congelarTela()
{
	char ch;
	printf("Digite 0 para continuar...\n");
	int input = getNumero();
	while (input != 0) {
		os_limparTela();
		input = getNumero();
	}
}
// STRING
int isLetra(char ch)
{
	if ((ch >= 97) && (ch <= 122))
		return 1;
	if ((ch >= 65) && (ch <= 90))
		return 1;

	return 0;
}
int isNumero(char ch)
{
	if ((ch >= 48) && (ch <= 57))
		return 1;

	return 0;
}
char tirarAcento(unsigned char ch)
{
	// 198 se refere ao � no ascii extended, que � o que getch e scanf pegam

	if (ch == 135) // �
		return ('C');

	if (ch == 198) // �
		return ('A');
	if (ch == 199) // �
		return ('A');
	if (ch == 131) // �
		return ('A');
	if (ch == 182) // �
		return ('A');
	if (ch == 160) // �
		return ('A');
	if (ch == 181) // �
		return ('A');
	if (ch == 133) // �
		return ('A');
	if (ch == 183) // �
		return ('A');
	if (ch == 132) // �
		return ('A');
	if (ch == 142) // �
		return ('A');

	if (ch == 130) // �
		return ('E');
	if (ch == 144) // �
		return ('E');
	if (ch == 138) // �
		return ('E');
	if (ch == 212) // �
		return ('E');
	if (ch == 136) // �
		return ('E');
	if (ch == 210) // �
		return ('E');
	if (ch == 137) // �
		return ('E');
	if (ch == 211) // �
		return ('E');

	if (ch == 161) // �
		return ('I');
	if (ch == 214) // �
		return ('I');
	if (ch == 141) // �
		return ('I');
	if (ch == 222) // �
		return ('I');

	if (ch == 162) // �
		return ('O');
	if (ch == 224) // �
		return ('O');
	if (ch == 149) // �
		return ('O');
	if (ch == 227) // �
		return ('O');
	if (ch == 147) // �
		return ('O');
	if (ch == 226) // �
		return ('O');
	if (ch == 228) // �
		return ('O');
	if (ch == 229) // �
		return ('O');
	if (ch == 148) // �
		return ('O');
	if (ch == 153) // �
		return ('O');

	if (ch == 163) // �
		return ('U');
	if (ch == 233) // �
		return ('U');
	if (ch == 151) // �
		return ('U');
	if (ch == 235) // �
		return ('U');
	if (ch == 129) // �
		return ('U');
	if (ch == 154) // �
		return ('U');

	return ch;
}
// DATE
int getDia()
{
	time_t timer = time(NULL);
	struct tm *now = localtime(&timer);

	return now->tm_mday;
}
int getMes()
{
	time_t timer = time(NULL);
	struct tm *now = localtime(&timer);

	return now->tm_mon + 1;
}
int getAno()
{
	time_t timer = time(NULL);
	struct tm *now = localtime(&timer);

	return now->tm_year + 1900;
}
int totalDiasMes(int mes, int ano)
{
	switch (mes)
	{
	case 0:
	case 2:
	case 4:
	case 6:
	case 7:
	case 9:
	case 11:
		return 31;
		break;

	case 3:
	case 5:
	case 8:
	case 10:
		return 30;
		break;

	case 1:
		if (!(ano % 4))
			return 29;
		else
			return 28;
		break;

	default:
		return 0;
		break;
	}
}
int diasEntreDuasDatas(int diaIni, int mesIni, int anoIni, int diaFim, int mesFim, int anoFim)
{
	int dI = diaIni, mI = mesIni;
	int aI = anoIni;
	int cDias = 0;
	int qtdeDiasMes;

	if (!((diaIni == diaFim) && (mesIni == mesFim) && (anoIni == anoFim)))
		do
		{
			qtdeDiasMes = totalDiasMes(mI, aI);
			if (dI == qtdeDiasMes)
			{
				dI = 1;
				++mI;
				++cDias;
				if (mI > 11)
				{
					mI = 0;
					++aI;
					qtdeDiasMes = totalDiasMes(mI, aI);
				}
				else
					qtdeDiasMes = totalDiasMes(mI, aI);
			}

			if (!((dI == diaFim) && (mI == mesFim) && (aI == anoFim)))
				for (; dI < qtdeDiasMes; dI++)
				{
					++cDias;
					if ((dI == diaFim) && (mI == mesFim) && (aI == anoFim))
					{
						--cDias;
						break;
					}
				}
		} while (!((dI == diaFim) && (mI == mesFim) && (aI == anoFim)));

	return cDias;
}
void os_system(const char *command)
{
	printf("Executing command: %s\n", command);
#ifdef _WIN32
	system(command);
#endif
#ifdef _MACOS
	system(command);
#endif
}
void os_setarTamanhoCorJanela(E_tamanhoJanela tamanho, E_corJanela cor)
{
	switch (tamanho)
	{
	case LINHAS_12:
#ifdef _WIN32
	os_os_system("mode con lines=12");
	os_os_system("mode con cols=62");
	os_os_system("color 4F");
#endif
		break;
	case LINHAS_60:
#ifdef _WIN32
	os_os_system("mode con lines=60");
	os_os_system("mode con cols=62");
	os_os_system("color 4F");
#endif
		break;
	default:
		break;
	}

	switch (cor)
	{
	case DEFAULT:
		os_system("color 4F");
		break;
	case VERDE:
		os_system("color 2F");
		break;
	case VERMELHO:
		os_system("color 4F");
		break;
	}
}

void os_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#endif
#ifdef _MACOS
	usleep(ms * 1000);
#endif
}

// UI
void splashScreen()
{
	os_setarTamanhoCorJanela(LINHAS_12, DEFAULT);
	os_limparTela();

	printf("\n");
	printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf(" @                                                          @\n");
	printf(" @                                                          @\n");
	printf(" @                       BOOKLENDING 2012                   @\n");
	printf(" @                                                          @\n");
	printf(" @                                                          @\n");
	printf(" @  Mauricio Ize                                            @\n");
	printf(" @                                                          @\n");
	printf(" @                                                          @\n");
	printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	os_sleep(1000);
	os_limparTela();
	os_setarTamanhoCorJanela(LINHAS_60, DEFAULT);
}

// ===================
int showPositiveIntegerField(const char *title, int *out) {
    char buffer[128];
    int value = 0;
    int found = 0;
    int i = 0;

    if (!out) return 0;

    /* Prompt */
    if (title) {
        printf("%s (int): ", title);
        fflush(stdout);
    }

    /* Read input line */
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;   /* EOF / error */
    }

    /* Skip leading whitespace */
    while (buffer[i] && isspace((unsigned char)buffer[i])) {
        i++;
    }

    /* Reject negative sign, reject '+' explicitly if you want */
    if (buffer[i] == '-' || buffer[i] == '+') {
        return 0; /* not allowed */
    }

    /* Must start with digit */
    if (!isdigit((unsigned char)buffer[i])) {
        return 0;
    }

    /* Collect digits */
    for (; buffer[i] != '\0'; i++) {
        if (isdigit((unsigned char)buffer[i])) {
            value = value * 10 + (buffer[i] - '0');
            found = 1;
        } else if (!isspace((unsigned char)buffer[i])) {
            /* Non-digit, non-space → invalid */
            return 0;
        }
    }

    if (!found) {
        return 0;  /* no digits found at all */
    }

    *out = value;
    return 1;
}
int showTextField(const char *title, char *buffer, size_t size) {
    if (!buffer || size == 0) {
        return 0;
    }
    /* Prompt */
    if (title) {
        printf("%s (char[%d]): ", title, (int)size);
        fflush(stdout);
    }
    /* Read input */
    if (!fgets(buffer, size, stdin)) {
        return 0;   /* EOF or error */
    }
    /* Remove trailing newline */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return 1;
}
int getNumero(void) {
    char buffer[128];
    /* Read a whole line */
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
    int value = 0;
    int found = 0;
    /* Collect all digits */
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (isdigit((unsigned char)buffer[i])) {
            value = value * 10 + (buffer[i] - '0');
            found = 1;
        }
    }
    return found ? value : -1;
}
// int getNumero()
// {
// 	char ch[2];
// 	int numero;

// 	do
// 	{
// 		fflush(stdin);
// #ifdef _WIN32
// 		ch[0] = getch();
// #endif
// #ifdef _MACOS
// 		ch[0] = getchar();
// #endif
// 		ch[1] = 0;
// 	} while (!isNumero(ch[0]));

// 	numero = atoi(ch);

// 	return numero;
// }

void mostrarTituloPequeno(char *titulo)
{
	os_limparTela();
	printf("\n");
	printf(" +==========================================================+\n");
	printf(" |                                                          |\n");
	printf(" |   %-54s |\n", titulo);
	printf(" |                                                          |\n");
	printf(" +==========================================================+\n");
	printf("\n");
}
void mostrarTituloGrande(char *titulo)
{
	printf(" +------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf(" |                                                                                                                                                            |\n");
	printf(" |   %-152s |\n", titulo);
	printf(" |                                                                                                                                                            |\n");
	printf(" +------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
}