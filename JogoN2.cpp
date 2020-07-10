#include<stdio.h>
#include<graphics.h>
#include <time.h>
#include <windows.h>

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC     27

#define TECLAENTER		13
#define TECLABACKSPACE	8
#define TECLAI			105

enum NomeDosMenus {MENUPRINCIPAL, CUSTOMIZACAOCARRO};
enum NomeDosMenusCustomizacao {MENUMOTOR, MENUTURBO, MENUREDPESO, MENUINJECAO, MENUSUSPENSAO, MENUNITRO, MENUPNEU};
enum NomeDosMapas {CIDADE, PRAIA, GRANDPRIX};

enum Motores {MOTOR1, MOTOR2, MOTOR3};
enum Turbos {TURBO1, TURBO2, TURBO3};
enum RedPeso {REDP1, REDP2, REDP3};
enum Injecao {INJECAO1, INJECAO2, INJECAO3};
enum Suspencao {SUSPENSAO1, SUSPENSAO2, SUSPENSAO3};
enum Nitro {NITRO1, NITRO2, NITRO3};
enum Pneu {PNEU1, PNEU2, PNEU3};

enum EfeitosSonorosNomes {VOL1, VOL2, VOL3, PARARMUSICA, MUSICAMENU, MUSICACORRIDA1, MUSICACORRIDA2, MUSICACORRIDA3, PARAREFEITOSONORO, SOMVITORIA, SOMSELECIONAR, SOMFALHA, SOMCOMPRA, SOMEQUIPAR, SOMNITRO};

struct StructFase
{
	int pos,
		comprimento,
		mapa;
		
	int motor,
		turbo,
		reducaoPeso,
		injecao,
		suspensao,
		nitro,
		pneu;
};

struct StructCarro
{
	int pos,
		posX,
		posY,
		tanque,
		velocidade,
		aceleracao,
		velocidadeMax;
	
	int motor,
		turbo,
		reducaoPeso,
		injecao,
		suspensao,
		nitro,
		pneu;
};

struct StructPecas
{
	char Nome[50];
	int Valor,
		Preco;
};

void tocarSom(int som);

bool iniciarCorrida(StructCarro jogador, StructCarro oponente, StructFase Fase[], void *R[], void *F[], int tamX, int tamY, int FaseAtual)
{
	bool resultado;
	
	int pg = 1;
	unsigned long long gt1, gt2;
	int FPS = 60;
	char tecla = 0;
	
	//Turbo
	int turboAceleracao = jogador.suspensao,
		turboVelocidadeMax = jogador.turbo,
		turboVelocidade = 0,
		tempoTurbo = 0;
	
	bool SpacePress = false,
		 turboAcelerando = false;
	
	Fase[FaseAtual].pos = 0;
	
	jogador.pos = 0;
	jogador.posX = 0;
	jogador.posY = 500;
	jogador.tanque = jogador.nitro;
	jogador.aceleracao = jogador.pneu;
	jogador.aceleracao += jogador.injecao;
	jogador.velocidade = 0;
	jogador.velocidadeMax = 25 * jogador.motor;
	jogador.velocidadeMax += (jogador.velocidadeMax * (jogador.reducaoPeso/10));
	
	oponente.motor=Fase[FaseAtual].motor;
	oponente.turbo=Fase[FaseAtual].turbo;
	oponente.reducaoPeso=Fase[FaseAtual].reducaoPeso;
	oponente.injecao=Fase[FaseAtual].injecao;
	oponente.suspensao=Fase[FaseAtual].suspensao;
	oponente.nitro=Fase[FaseAtual].nitro;
	oponente.pneu=Fase[FaseAtual].pneu;
	
	oponente.pos =0;
	oponente.posX = 0;
	oponente.posY = 400;
	oponente.tanque = oponente.nitro;
	oponente.aceleracao = oponente.pneu;
	oponente.aceleracao += oponente.injecao;
	oponente.velocidade = 0;
	oponente.velocidadeMax = 26 * oponente.motor;
	oponente.velocidadeMax += (oponente.velocidadeMax * (oponente.reducaoPeso/10));
	
	gt1 = GetTickCount();
	
	while (jogador.posX < 890)
	{
		gt2 = GetTickCount();
		if (gt2 - gt1 > 1000/FPS)
		{
			gt1 = gt2;
			
			if(pg == 1) pg = 2; else pg = 1;
			setactivepage(pg);
			setbkcolor(RGB(0,0,0));
			cleardevice();
					
			//Desenhar a fase
			if(Fase[FaseAtual].mapa==CIDADE)
			{
				putimage(Fase[FaseAtual].pos, 0, F[0], COPY_PUT);
				putimage(Fase[FaseAtual].pos+tamX, 0, F[0], COPY_PUT);
				putimage(Fase[FaseAtual].pos+(tamX*2), 0, F[1], COPY_PUT);
			}
			
			if(Fase[FaseAtual].mapa==PRAIA)
			{
				putimage(Fase[FaseAtual].pos, 0, F[2], COPY_PUT);
				putimage(Fase[FaseAtual].pos+tamX, 0, F[2], COPY_PUT);
				putimage(Fase[FaseAtual].pos+(tamX*2), 0, F[3], COPY_PUT);
			}
			
			if(Fase[FaseAtual].mapa==GRANDPRIX)
			{
				putimage(Fase[FaseAtual].pos, 0, F[4], COPY_PUT);
				putimage(Fase[FaseAtual].pos+tamX, 0, F[4], COPY_PUT);
				putimage(Fase[FaseAtual].pos+(tamX*2), 0, F[5], COPY_PUT);
			}
			
			
			
			setfillstyle(1,RGB(255,0,0));
			bar(oponente.posX, oponente.posY, oponente.posX+100, oponente.posY + 50);
			
			setfillstyle(1,RGB(0,255,0));
			bar(jogador.posX, jogador.posY, jogador.posX+100, jogador.posY + 50);
			
			//Deixa a pagina visivel
			setvisualpage(pg);
			
			//Movimentação do jogador
			//Comandos
			if(GetKeyState(0x44)&0x80)
			{
				jogador.velocidade += jogador.aceleracao;
			}
			else if(GetKeyState(0x41)&0x80)
			{
				jogador.velocidade -= jogador.aceleracao*5;
			}
			else if(jogador.velocidade > 0)
			{
				jogador.velocidade --;
			}
			
			if((GetKeyState(VK_SPACE)&0x80) && (SpacePress == false) && (jogador.tanque > 0))
			{
				tocarSom(SOMNITRO);
				tempoTurbo = 120;
				jogador.tanque -= 500;
				turboAcelerando = true;
			}
			
			if(tempoTurbo > 0)
			{
				if(turboAcelerando == true)
				{
					turboVelocidade += turboAceleracao;
					if(turboVelocidade > turboVelocidadeMax)
					{
						turboVelocidade = turboVelocidadeMax;
						turboAcelerando = false;
					}
				}
				
				tempoTurbo --;
			}
			else
			{
				if(turboVelocidade > 0)
				{
					turboVelocidade --;
				}
			}
			
			/*
			printf("\n\nTurbo Velocidade: %d", turboVelocidade);
			printf("\nTurbo Acelerando:   %d", turboAcelerando);
			printf("\nJogador Tanque: 	  %d", jogador.tanque);
			printf("\nTurbo Tempo: 		  %d", tempoTurbo);
			*/
			
			//Controle das velocidades
			if(jogador.velocidade > jogador.velocidadeMax)
			{
				jogador.velocidade = jogador.velocidadeMax;
			}
			if(jogador.velocidade < 0)
			{
				jogador.velocidade = 0;
			}

		    if(oponente.velocidade <= oponente.velocidadeMax)
			{
				oponente.velocidade += oponente.aceleracao;
			}
			if(oponente.velocidade > oponente.velocidadeMax)
			{
				oponente.velocidade = oponente.velocidadeMax;
			}
			
			//Alterar as posicoes dos carros
			if(oponente.pos < Fase[FaseAtual].comprimento + 2000)
			{
				oponente.pos += oponente.velocidade;
				oponente.posX += oponente.velocidade;
			}
		    
		    jogador.pos += jogador.velocidade + turboVelocidade;
			
			if((jogador.posX > tamX / 3) && (Fase[FaseAtual].pos > -2000))
			{
				Fase[FaseAtual].pos -= jogador.velocidade + turboVelocidade;
				oponente.posX -= jogador.velocidade + turboVelocidade;
				if((Fase[FaseAtual].pos < -(tamX)) && ((Fase[FaseAtual].comprimento - jogador.pos) > 2000))
				{
					Fase[FaseAtual].pos += tamX;
				}
				
				if(Fase[FaseAtual].pos < -2000)
				{
					Fase[FaseAtual].pos = -2000;
				}
			}
			else
			{
				jogador.posX += jogador.velocidade + turboVelocidade;
			}
			/*
			printf("\n\nJogador PosX: %d", jogador.pos);
			printf("\nJogador Vel: %d", jogador.velocidade);
			printf("\nOponente PosX: %d", oponente.pos);
			printf("\nOponente Vel: %d", oponente.velocidade);
			*/
			
			if((GetKeyState(VK_SPACE)&0x80))
		    {
		    	SpacePress = true;
			}
			if(!(GetKeyState(VK_SPACE)&0x80))
	      	{
	      		SpacePress = false;
			}
			
			tecla = 0;
			fflush(stdin);
			if (kbhit())
			{
				tecla = getch();
			}
		}
	}
	
	if (jogador.pos > oponente.pos)
	{ //Ganhou
		resultado = true;
	}
	else
	{ //Perdeu
		resultado = false;
	}

	return(resultado);
}

int main()
{	
	//Imagens
	void *F[6];
	void *R[3]; // Teste
	
	//Variaveis do jogo
	int gold = 0,
		FaseAtual = 0;
	
	StructCarro jogador,
		  		oponente;
		  
	StructFase Fase[9];
	
	Fase[0].mapa = CIDADE;
	Fase[0].pos = 0,
	Fase[0].comprimento = 15000;
	Fase[0].motor = 1;
	Fase[0].reducaoPeso = 1;
	Fase[0].injecao = 1;
	Fase[0].suspensao = 1;
	Fase[0].nitro = 1000;
	Fase[0].pneu = 1;
	
	Fase[1].mapa = CIDADE;
	Fase[1].pos = 0,
	Fase[1].comprimento = 20000;
	Fase[1].motor = 1;
	Fase[1].reducaoPeso = 1;
	Fase[1].injecao = 1;
	Fase[1].suspensao = 1;
	Fase[1].nitro = 1000;
	Fase[1].pneu = 1;
	
	Fase[2].mapa = CIDADE;
	Fase[2].pos = 0,
	Fase[2].comprimento = 25000;
	Fase[2].motor = 2;
	Fase[2].reducaoPeso = 1;
	Fase[2].injecao = 1;
	Fase[2].suspensao = 1;
	Fase[2].nitro = 1000;
	Fase[2].pneu = 1;
	
	Fase[3].mapa = PRAIA;
	Fase[3].pos = 0,
	Fase[3].comprimento = 35000;
	Fase[3].motor = 2;
	Fase[3].reducaoPeso = 2;
	Fase[3].injecao = 2;
	Fase[3].suspensao = 3;
	Fase[3].nitro = 1500;
	Fase[3].pneu = 2;
	
	Fase[4].mapa = PRAIA;
	Fase[4].pos = 0,
	Fase[4].comprimento = 40000;
	Fase[4].motor = 3;
	Fase[4].reducaoPeso = 2;
	Fase[4].injecao = 2;
	Fase[4].suspensao = 3;
	Fase[4].nitro = 1500;
	Fase[4].pneu = 2;
	
	Fase[5].mapa = PRAIA;
	Fase[5].pos = 0,
	Fase[5].comprimento = 45000;
	Fase[5].motor = 3;
	Fase[5].reducaoPeso = 2;
	Fase[5].injecao = 2;
	Fase[5].suspensao = 3;
	Fase[5].nitro = 1500;
	Fase[5].pneu = 2;
	
	Fase[6].mapa = GRANDPRIX;
	Fase[6].pos = 0,
	Fase[6].comprimento = 50000;
	Fase[6].motor = 4;
	Fase[6].reducaoPeso = 3;
	Fase[6].injecao = 3;
	Fase[6].suspensao = 5;
	Fase[6].nitro = 1500;
	Fase[6].pneu = 3;
	
	Fase[7].mapa = GRANDPRIX;
	Fase[7].pos = 0,
	Fase[7].comprimento = 55000;
	Fase[7].motor = 4;
	Fase[7].reducaoPeso = 3;
	Fase[7].injecao = 3;
	Fase[7].suspensao = 5;
	Fase[7].nitro = 1500;
	Fase[7].pneu = 3;
	
	Fase[8].mapa = GRANDPRIX;
	Fase[8].pos = 0,
	Fase[8].comprimento = 60000;
	Fase[8].motor = 5;
	Fase[8].reducaoPeso = 3;
	Fase[8].injecao = 3;
	Fase[8].suspensao = 5;
	Fase[8].nitro = 1500;
	Fase[8].pneu = 3;
	
	//Variaveis de controle
	int pg = 1,
		tamX = 1000,
		tamY = 600,
		FPS = 60,
		tamImagem = 0,
		i = 0,
		Selecao = 0,
		quantidadeDeCorridas = 0;
	
	char tecla = 0,
		 Texto[50],
		 Texto2[50];
	
	unsigned long long gt1, gt2;
	
	//Variaveis dos menus
	int menuAtual = 0,
		menuAtual2 = 0;
	
	bool result = false,
		 comecarCorrida = false;
	
	int Menu1PosX = 60,
		Menu1PosY = 190,
		Menu1PosYD = 45;
	
	//Ponteiros --------------------------------------------------------------------
	int ListaMotoresTamanho = 1,
		*ListaMotores = NULL;
	
	int ListaTurbosTamanho = 1,
		*ListaTurbos = NULL;
		
	int ListaRedPesosTamanho = 1,
		*ListaRedPesos = NULL;
	
	int ListaInjecoesTamanho = 1,
		*ListaInjecoes = NULL;
	
	int ListaSuspensoresTamanho = 1,
		*ListaSuspensores = NULL;
	
	int ListaNitrosTamanho = 1,
		*ListaNitros = NULL;
	
	int ListaPneusTamanho = 1,
		*ListaPneus = NULL;
	
	ListaMotores = (int *)realloc(ListaMotores, sizeof(int) * ListaMotoresTamanho);
	ListaMotores[ListaMotoresTamanho - 1] = MOTOR1;
	
	ListaTurbos = (int *)realloc(ListaTurbos, sizeof(int) * ListaTurbosTamanho);
	ListaTurbos[ListaTurbosTamanho - 1] = TURBO1;
	
	ListaRedPesos = (int *)realloc(ListaRedPesos, sizeof(int) * ListaRedPesosTamanho);
	ListaRedPesos[ListaRedPesosTamanho - 1] = REDP1;
	
	ListaInjecoes = (int *)realloc(ListaInjecoes, sizeof(int) * ListaInjecoesTamanho);
	ListaInjecoes[ListaInjecoesTamanho - 1] = INJECAO1;
	
	ListaSuspensores = (int *)realloc(ListaSuspensores, sizeof(int) * ListaSuspensoresTamanho);
	ListaSuspensores[ListaSuspensoresTamanho - 1] = SUSPENSAO1;
	
	ListaNitros = (int *)realloc(ListaNitros, sizeof(int) * ListaNitrosTamanho);
	ListaNitros[ListaNitrosTamanho - 1] = NITRO1;
	
	ListaPneus = (int *)realloc(ListaPneus, sizeof(int) * ListaPneusTamanho);
	ListaPneus[ListaPneusTamanho - 1] = PNEU1;
	
	
	//Peças ------------------------------------------------------------------------
	
	//Motores
	StructPecas Motor[3];
	
	strcpy(Motor[MOTOR1].Nome, "1.8 - AP Turbo 4 Cilindros");
	Motor[MOTOR1].Valor = 1;
	Motor[MOTOR1].Preco = 0;
	
	strcpy(Motor[MOTOR2].Nome, "2.0 - 4 Cilindros Forjado");
	Motor[MOTOR2].Valor = 3;
	Motor[MOTOR2].Preco = 300;
	
	strcpy(Motor[MOTOR3].Nome, "3.0 - 6 Cilindros em Linha 2JZ");
	Motor[MOTOR3].Valor = 5;
	Motor[MOTOR3].Preco = 600;
	
	//Turbos
	StructPecas Turbo[3];
	
	strcpy(Turbo[TURBO1].Nome, "Turbo Garret .42");
	Turbo[TURBO1].Valor = 20;
	Turbo[TURBO1].Preco = 0;
	
	strcpy(Turbo[TURBO2].Nome, "Turbo Garret .50");
	Turbo[TURBO2].Valor = 40;
	Turbo[TURBO2].Preco = 100;
	
	strcpy(Turbo[TURBO3].Nome, "Twin Turbo");
	Turbo[TURBO3].Valor = 60;
	Turbo[TURBO3].Preco = 300;
	
	//Redutores de Peso
	StructPecas RedutorPeso[3];
	
	strcpy(RedutorPeso[REDP1].Nome, "Reducao de 10%");
	RedutorPeso[REDP1].Valor = 1;
	RedutorPeso[REDP1].Preco = 0;
	
	strcpy(RedutorPeso[REDP2].Nome, "Reducao de 20%");
	RedutorPeso[REDP2].Valor = 2;
	RedutorPeso[REDP2].Preco = 50;
	
	strcpy(RedutorPeso[REDP3].Nome, "Reducao de 30%");
	RedutorPeso[REDP3].Valor = 3;
	RedutorPeso[REDP3].Preco = 100;
	
	//Injecoes
	StructPecas Injecao[3];
	
	strcpy(Injecao[INJECAO1].Nome, "Carburado");
	Injecao[INJECAO1].Valor = 1;
	Injecao[INJECAO1].Preco = 0;
	
	strcpy(Injecao[INJECAO2].Nome, "Injeção Eletrônica");
	Injecao[INJECAO2].Valor = 2;
	Injecao[INJECAO2].Preco = 50;
	
	strcpy(Injecao[INJECAO3].Nome, "Injeção Reprogramada");
	Injecao[INJECAO3].Valor = 3;
	Injecao[INJECAO3].Preco = 100;
	
	//Suspensores
	StructPecas Suspensao[3];
	
	strcpy(Suspensao[SUSPENSAO1].Nome, "Fixa");
	Suspensao[SUSPENSAO1].Valor = 1;
	Suspensao[SUSPENSAO1].Preco = 0;
	
	strcpy(Suspensao[SUSPENSAO2].Nome, "McPherson");
	Suspensao[SUSPENSAO2].Valor = 3;
	Suspensao[SUSPENSAO2].Preco = 50;
	
	strcpy(Suspensao[SUSPENSAO3].Nome, "Multilink");
	Suspensao[SUSPENSAO3].Valor = 5;
	Suspensao[SUSPENSAO3].Preco = 100;
	
	//Nitros
	StructPecas Nitro[3];
	
	strcpy(Nitro[NITRO1].Nome, "Cilindro de 1L");
	Nitro[NITRO1].Valor = 1000;
	Nitro[NITRO1].Preco = 0;
	
	strcpy(Nitro[NITRO2].Nome, "Cilindro de 1,5L");
	Nitro[NITRO2].Valor = 1500;
	Nitro[NITRO2].Preco = 100;
	
	strcpy(Nitro[NITRO3].Nome, "Cilindro de 2,5L");
	Nitro[NITRO3].Valor = 2500;
	Nitro[NITRO3].Preco = 200;
	
	//Pneus
	StructPecas Pneu[3];
	
	strcpy(Pneu[PNEU1].Nome, "Pneus Comuns");
	Pneu[PNEU1].Valor = 1;
	Pneu[PNEU1].Preco = 0;
	
	strcpy(Pneu[PNEU2].Nome, "Pneus Intemediarios");
	Pneu[PNEU2].Valor = 2;
	Pneu[PNEU2].Preco = 50;
	
	strcpy(Pneu[PNEU3].Nome, "Pneus Profissionais");
	Pneu[PNEU3].Valor = 3;
	Pneu[PNEU3].Preco = 100;
	
	//Jogador
	jogador.pos = 0;
	jogador.posX = 0;
	jogador.aceleracao = 0;
	jogador.velocidade = 0;
	jogador.velocidadeMax = 0;
	
	jogador.motor = Motor[0].Valor;
	jogador.turbo = Turbo[0].Valor;
	jogador.reducaoPeso = RedutorPeso[0].Valor;
	jogador.injecao = Injecao[0].Valor;
	jogador.suspensao = Suspensao[0].Valor;
	jogador.nitro = Nitro[0].Valor;
	jogador.pneu = Pneu[0].Valor;
	
	//Iniciar a janela do jogo ----------------------------------------------------------------------------------------------
	initwindow(tamX, tamY, "Click Tuning", 50, 50);
	
	tamImagem = imagesize(0, 0, 1000 - 1, 600 - 1);
	R[0] = malloc(tamImagem);
	R[1] = malloc(tamImagem);
	R[2] = malloc(imagesize(0, 0, 335 - 1, 45 - 1));
	
	//Imagens das fases
	F[0] = malloc(tamImagem);
	F[1] = malloc(tamImagem);
	F[2] = malloc(tamImagem);
	F[3] = malloc(tamImagem);
	F[4] = malloc(tamImagem);
	F[5] = malloc(tamImagem);
	
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[0]);
	readimagefile("Sprites/FundoTutorialeFase1Chegada.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[1]);
	
	readimagefile("Sprites/FundoFase2.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[2]);
	readimagefile("Sprites/FundoFase2Chegada.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[3]);
	
	readimagefile("Sprites/FundoFase3.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[4]);
	readimagefile("Sprites/FundoFase3Chegada.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, F[5]);
	
	
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, R[0]);
	readimagefile("Sprites/FundoTutorialeFase1Chegada.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, R[1]);
	
	
	readimagefile("Sprites/menuCustomizacao1.bmp", 0, 0, 335 - 1, 45 - 1);
	getimage(0, 0, 335 - 1, 45 - 1, R[2]);
	
	menuAtual = MENUPRINCIPAL;
	menuAtual = CUSTOMIZACAOCARRO;
	tocarSom(VOL2);
	tocarSom(MUSICAMENU);
	while(tecla != ESC)
	{
		while(menuAtual == MENUPRINCIPAL && tecla != ESC)
		{
			//Alguma coisa
		}
		
		while(menuAtual == CUSTOMIZACAOCARRO && tecla != ESC)
		{
			gt2 = GetTickCount();
			if (gt2 - gt1 > 1000/FPS)
			{
				gt1 = gt2;
				
				if(pg == 1) pg = 2; else pg = 1;
				
				setactivepage(pg);
				setbkcolor(RGB(230, 230, 230));
				cleardevice();
				
				//Desenhos
				
				//Menu de customizacao
				//Desenhos do menu
				
				//Mostrar coisas do jogador
				setbkcolor(RGB(237, 28, 36));
				setcolor(RGB(0, 0, 0));
				setlinestyle(0, 0, 1);
				
				strcpy(Texto, "Dinheiro: R$ ");
				itoa(gold, Texto2, 10);
				strcat(Texto, Texto2);
				outtextxy(700, 20, Texto);
				
				if(menuAtual2 == MENUMOTOR)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaMotoresTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Motor[ListaMotores[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Motor[ListaMotores[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Motor[ListaMotores[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUTURBO)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaTurbosTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Turbo[ListaTurbos[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Turbo[ListaTurbos[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Turbo[ListaTurbos[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUREDPESO)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaRedPesosTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, RedutorPeso[ListaRedPesos[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(RedutorPeso[ListaRedPesos[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(RedutorPeso[ListaRedPesos[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUINJECAO)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaInjecoesTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Injecao[ListaInjecoes[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Injecao[ListaInjecoes[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Injecao[ListaInjecoes[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUSUSPENSAO)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaSuspensoresTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Suspensao[ListaSuspensores[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Suspensao[ListaSuspensores[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Suspensao[ListaSuspensores[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUNITRO)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaNitrosTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Nitro[ListaNitros[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Nitro[ListaNitros[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Nitro[ListaNitros[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUPNEU)
				{
					setbkcolor(RGB(237, 28, 36));
					setcolor(RGB(0, 0, 0));
					setlinestyle(0, 0, 1);
					
					for(i = 0; i < ListaPneusTamanho; i++)
					{
						putimage(Menu1PosX, Menu1PosY + (Menu1PosYD * i), R[2], COPY_PUT);
						
						strcpy(Texto, Pneu[ListaPneus[i]].Nome);
						outtextxy(Menu1PosX + 10, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
						
						if(Pneu[ListaPneus[i]].Preco > 0)
						{
							strcpy(Texto, "Preco: ");
							itoa(Pneu[ListaPneus[i]].Preco, Texto2, 10);
							strcat(Texto, Texto2);
						}
						else
						{
							strcpy(Texto, "Adquirido");
						}
						
						outtextxy(Menu1PosX + 250, Menu1PosY + (Menu1PosYD * i) + 15, Texto);
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//Deixa a pagina visivel
				setvisualpage(pg);
				
				//--------------------------------------------------------------------------------------------------------------------------
				
				//Acoes
				//Menu de customizacao
				if(tecla == RIGHT)
				{
					tocarSom(SOMSELECIONAR);
					menuAtual2 ++;
					Selecao = 0;
					if(menuAtual2 > 6)
					{
						menuAtual2 = 0;
					}
				}
				
				if(tecla == LEFT)
				{
					tocarSom(SOMSELECIONAR);
					menuAtual2 --;
					Selecao = 0;
					if(menuAtual2 < 0)
					{
						menuAtual2 = 6;
					}
				}
				
				if(tecla == TECLAI)
				{
					comecarCorrida = true;
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUMOTOR)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaMotoresTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Motor[ListaMotores[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.motor = Motor[ListaMotores[Selecao]].Valor;
							printf("\nMotor: %d", jogador.motor);
						}
						else
						{
							if(gold >= Motor[ListaMotores[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Motor[ListaMotores[Selecao]].Preco;
								Motor[ListaMotores[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUTURBO)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaTurbosTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Turbo[ListaTurbos[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.turbo = Turbo[ListaTurbos[Selecao]].Valor;
							printf("\nTurbo: %d", jogador.turbo);
						}
						else
						{
							if(gold >= Turbo[ListaTurbos[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Turbo[ListaTurbos[Selecao]].Preco;
								Turbo[ListaTurbos[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUREDPESO)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaRedPesosTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(RedutorPeso[ListaRedPesos[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.reducaoPeso = RedutorPeso[ListaRedPesos[Selecao]].Valor;
							printf("\nRedutor de Peso: %d", jogador.reducaoPeso);
						}
						else
						{
							if(gold >= RedutorPeso[ListaRedPesos[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= RedutorPeso[ListaRedPesos[Selecao]].Preco;
								RedutorPeso[ListaRedPesos[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUINJECAO)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaInjecoesTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Injecao[ListaInjecoes[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.injecao = Injecao[ListaInjecoes[Selecao]].Valor;
							printf("\nInjecao: %d", jogador.injecao);
						}
						else
						{
							if(gold >= Injecao[ListaInjecoes[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Injecao[ListaInjecoes[Selecao]].Preco;
								Injecao[ListaInjecoes[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUSUSPENSAO)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaSuspensoresTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Suspensao[ListaSuspensores[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.suspensao = Suspensao[ListaSuspensores[Selecao]].Valor;
							printf("\nSuspensao: %d", jogador.suspensao);
						}
						else
						{
							if(gold >= Suspensao[ListaSuspensores[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Suspensao[ListaSuspensores[Selecao]].Preco;
								Suspensao[ListaSuspensores[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUNITRO)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaNitrosTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Nitro[ListaNitros[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.nitro = Nitro[ListaNitros[Selecao]].Valor;
							printf("\nNitro: %d", jogador.nitro);
						}
						else
						{
							if(gold >= Nitro[ListaNitros[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Nitro[ListaNitros[Selecao]].Preco;
								Nitro[ListaNitros[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//--------------------------------------------------------------------------------------------------------------------------
				if(menuAtual2 == MENUPNEU)
				{
					if(tecla == UP && Selecao > 0)
					{
						tocarSom(SOMSELECIONAR);
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaPneusTamanho - 1)
					{
						tocarSom(SOMSELECIONAR);
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						if(Pneu[ListaPneus[Selecao]].Preco <= 0)
						{
							tocarSom(SOMEQUIPAR);
							jogador.pneu = Pneu[ListaPneus[Selecao]].Valor;
							printf("\nPneu: %d", jogador.pneu);
						}
						else
						{
							if(gold >= Pneu[ListaPneus[Selecao]].Preco)
							{
								tocarSom(SOMCOMPRA);
								gold -= Pneu[ListaPneus[Selecao]].Preco;
								Pneu[ListaPneus[Selecao]].Preco = 0;
							}
							else
							{
								tocarSom(SOMFALHA);
							}
						}
					}
				}
				
				//Corrida -------------------------------------------------------------------------------------------
				if(comecarCorrida == true)
				{
					quantidadeDeCorridas ++;
					
					tocarSom(PARARMUSICA);
					if(Fase[FaseAtual].mapa == CIDADE)
					{
						tocarSom(MUSICACORRIDA1);
					}
					else if (Fase[FaseAtual].mapa == PRAIA)
					{
						tocarSom(MUSICACORRIDA2);
					}
					else if (Fase[FaseAtual].mapa == GRANDPRIX)
					{
						tocarSom(MUSICACORRIDA3);
					}
					result = iniciarCorrida(jogador, oponente, Fase, R, F, tamX, tamY, FaseAtual);
					tocarSom(PARARMUSICA);
					tocarSom(MUSICAMENU);
					
					if(result == true)
					{
						tocarSom(SOMVITORIA);
						gold += 100 + (100*FaseAtual) + (5*quantidadeDeCorridas);
						
						if(FaseAtual < 8)
						{
							FaseAtual ++;
						}
					}
					else
					{
						tocarSom(SOMFALHA);
						gold += (100 + (100*FaseAtual) + (5*quantidadeDeCorridas)) / 2;
					}
					
					switch(quantidadeDeCorridas)
					{
						case 1:
							ListaPneusTamanho ++;
							ListaPneus = (int *)realloc(ListaPneus, sizeof(int) * ListaPneusTamanho);
							ListaPneus[ListaPneusTamanho - 1] = PNEU2;
							break;
						
						case 2:
							ListaSuspensoresTamanho ++;
							ListaSuspensores = (int *)realloc(ListaSuspensores, sizeof(int) * ListaSuspensoresTamanho);
							ListaSuspensores[ListaSuspensoresTamanho - 1] = SUSPENSAO2;
							break;
						
						case 3:
							ListaInjecoesTamanho ++;
							ListaInjecoes = (int *)realloc(ListaInjecoes, sizeof(int) * ListaInjecoesTamanho);
							ListaInjecoes[ListaInjecoesTamanho - 1] = INJECAO2;
							break;
						
						case 4:
							ListaMotoresTamanho ++;
							ListaMotores = (int *)realloc(ListaMotores, sizeof(int) * ListaMotoresTamanho);
							ListaMotores[ListaMotoresTamanho - 1] = MOTOR2;
							break;
						
						case 5:
							ListaRedPesosTamanho ++;
							ListaRedPesos = (int *)realloc(ListaRedPesos, sizeof(int) * ListaRedPesosTamanho);
							ListaRedPesos[ListaRedPesosTamanho - 1] = REDP2;
							break;
						
						case 6:
							ListaTurbosTamanho ++;
							ListaTurbos = (int *)realloc(ListaTurbos, sizeof(int) * ListaTurbosTamanho);
							ListaTurbos[ListaTurbosTamanho - 1] = TURBO2;
							break;
						
						case 7:
							ListaNitrosTamanho ++;
							ListaNitros = (int *)realloc(ListaNitros, sizeof(int) * ListaNitrosTamanho);
							ListaNitros[ListaNitrosTamanho - 1] = NITRO2;
							break;
						
						case 8:
							ListaMotoresTamanho ++;
							ListaMotores = (int *)realloc(ListaMotores, sizeof(int) * ListaMotoresTamanho);
							ListaMotores[ListaMotoresTamanho - 1] = MOTOR3;
							break;
						
						case 9:
							ListaSuspensoresTamanho ++;
							ListaSuspensores = (int *)realloc(ListaSuspensores, sizeof(int) * ListaSuspensoresTamanho);
							ListaSuspensores[ListaSuspensoresTamanho - 1] = SUSPENSAO3;
							break;
						
						case 10:
							ListaInjecoesTamanho ++;
							ListaInjecoes = (int *)realloc(ListaInjecoes, sizeof(int) * ListaInjecoesTamanho);
							ListaInjecoes[ListaInjecoesTamanho - 1] = INJECAO3;
							break;
						
						case 11:
							ListaNitrosTamanho ++;
							ListaNitros = (int *)realloc(ListaNitros, sizeof(int) * ListaNitrosTamanho);
							ListaNitros[ListaNitrosTamanho - 1] = NITRO3;
							break;
						
						case 12:
							ListaRedPesosTamanho ++;
							ListaRedPesos = (int *)realloc(ListaRedPesos, sizeof(int) * ListaRedPesosTamanho);
							ListaRedPesos[ListaRedPesosTamanho - 1] = REDP3;
							break;
						
						case 13:
							ListaPneusTamanho ++;
							ListaPneus = (int *)realloc(ListaPneus, sizeof(int) * ListaPneusTamanho);
							ListaPneus[ListaPneusTamanho - 1] = PNEU3;
							break;
						
						case 14:
							ListaTurbosTamanho ++;
							ListaTurbos = (int *)realloc(ListaTurbos, sizeof(int) * ListaTurbosTamanho);
							ListaTurbos[ListaTurbosTamanho - 1] = TURBO3;
							break;
					}
					
					
					comecarCorrida = false;
				}
				
				tecla = 0;
				fflush(stdin);
				if (kbhit())
				{
					tecla = getch ();
					//printf("\n%d", tecla);
				}
			}
		}
	}
	
	free(ListaMotores);
	free(ListaTurbos);
	free(ListaRedPesos);
	free(ListaInjecoes);
	free(ListaSuspensores);
	free(ListaNitros);
	free(ListaPneus);
	
	closegraph();
	return (0);
}

void tocarSom(int som)
{
	//Alterar o volume dos sons
	if (som == VOL1)
	{
		waveOutSetVolume(0,0x01111111); //Volume no baixo
	}
    else if (som == VOL2)
    {
    	waveOutSetVolume(0,0x88888888); //Volume no médio
	}
    else if (som == VOL3)
    {
    	waveOutSetVolume(0,0xFFFFFFFF); //Volume no maximo
	}
	
	//Reproduzir sons de fundo
	else if (som == PARARMUSICA)
	{
		mciSendString("close musica", NULL, 0, 0);    //Para a reprodução do alias musica
	}
	else if (som == MUSICAMENU)
	{
		mciSendString("open .\\Sons\\menu.mp3 type MPEGVideo alias musica", NULL, 0, 0);
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	else if (som == MUSICACORRIDA1)
	{
		mciSendString("open .\\Sons\\fall-out-boy-sunshine-riptide-feat-burna-boy-instrumental.mp3 type MPEGVideo alias musica", NULL, 0, 0);
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	else if (som == MUSICACORRIDA2)
	{
		mciSendString("open .\\Sons\\the-white-stripes-seven-nation-army.mp3 type MPEGVideo alias musica", NULL, 0, 0); 
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	else if (som == MUSICACORRIDA3)
	{
		mciSendString("open .\\Sons\\travis-scott-highest-in-the-room-instrumental.mp3 type MPEGVideo alias musica", NULL, 0, 0);
      	mciSendString("play musica repeat", NULL, 0, 0);
	}
	
	//Reproduzir efeitos sonoros
	else if (som == PARAREFEITOSONORO)
	{
		//sndPlaySound(NULL, NULL); // Interrompe o som wav
	}
	else if(som == SOMVITORIA)
	{
		sndPlaySound(".\\Sons\\win.wav", SND_ASYNC);
	}
    else if (som == SOMSELECIONAR)
    {
    	//Exemplo de som em looping infinito.
    	//sndPlaySound(".\\sons\\barracks.wav", SND_ASYNC + SND_LOOP);
    	sndPlaySound(".\\Sons\\select.wav", SND_ASYNC);
	}
	else if (som == SOMFALHA)
    {
    	sndPlaySound(".\\Sons\\fail.wav", SND_ASYNC);
	}
	else if (som == SOMCOMPRA)
    {
    	sndPlaySound(".\\Sons\\compra.wav", SND_ASYNC);
	}
	else if (som == SOMEQUIPAR)
    {
    	sndPlaySound(".\\Sons\\pneumatica.wav", SND_ASYNC);
	}
	else if (som == SOMNITRO)
    {
    	sndPlaySound(".\\Sons\\nitro.wav", SND_ASYNC);
	}
}
