 //JOGNA2 - GRUPO 6

#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include <time.h>

#define CR	13

enum NomeDosMenus {MENUPRINCIPAL, CUSTOMIZACAOCARRO};
enum NomeDosMenusCustomizacao {MENUMOTOR, MENUTURBO, MENUREDPESO, MENUINJECAO, MENUSUSPENSAO, MENUNITRO, MENUPNEU};

enum Motores {MOTOR1, MOTOR2, MOTOR3};
enum Turbos {TURBO1, TURBO2, TURBO3};
enum RedPeso {REDP1, REDP2, REDP3};
enum Injecao {INJECAO1, INJECAO2, INJECAO3};
enum Suspencao {SUSPENSAO1, SUSPENSAO2, SUSPENSAO3};
enum Nitro {NITRO1, NITRO2, NITRO3};
enum Pneu {PNEU1, PNEU2, PNEU3};

struct StructFase
{
	int pos,
		comprimento;
};

struct StructCarro
{
	int pos,
		posX,
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

bool iniciarCorrida(StructCarro jogador, StructCarro oponente, StructFase Fase, void *R[], int tamX, int tamY){
	bool resultado;
	
	int pg = 1;
	unsigned long long gt1, gt2;
	int FPS = 60;
	
	jogador.pos = Fase.pos;
	jogador.aceleracao = 5;
	oponente.aceleracao = 1;
	oponente.pos =0;
	oponente.velocidade = 0;
	
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
			putimage(Fase.pos, 0, R[0], COPY_PUT);
			putimage(Fase.pos+tamX, 0, R[0], COPY_PUT);
			putimage(Fase.pos+(tamX*2), 0, R[1], COPY_PUT);
			
			setfillstyle(1,RGB(0,255,0));
			bar(jogador.posX,520,jogador.posX+100,570);
			setfillstyle(1,RGB(255,0,0));
			bar(oponente.posX,400,oponente.posX+100,450);
			
			//Deixa a pagina visivel
			setvisualpage(pg);
			
			//Movimentação do jogador
			//jogador.velocidade = 0;
			
			if(GetKeyState(VK_RIGHT)&0x80)
			{
				jogador.velocidade += jogador.aceleracao;
				if(jogador.velocidade > jogador.velocidadeMax)
				{
					jogador.velocidade = jogador.velocidadeMax;
				}
			}
			else if(GetKeyState(VK_LEFT)&0x80)
			{
				jogador.velocidade -= jogador.aceleracao*5;
				if(jogador.velocidade < 0)
				{
					jogador.velocidade = 0;
				}
			}
			else if(GetKeyState(VK_SPACE)&0x80)
			{
				jogador.velocidade += jogador.aceleracao*5;
			}

		    if(oponente.velocidade <= oponente.velocidadeMax){
				oponente.velocidade += oponente.aceleracao;
			}
			if(oponente.pos < Fase.comprimento + 2000)
			{
				oponente.pos += oponente.velocidade;
				oponente.posX += oponente.velocidade;
			}
		    
		    jogador.pos += jogador.velocidade;
			
			if((jogador.posX > tamX / 3) && (Fase.pos > -2000))
			{
				Fase.pos -= jogador.velocidade;
				oponente.posX -= jogador.velocidade;
				if((Fase.pos < -(tamX)) && ((Fase.comprimento - jogador.pos) > 2000))
				{
					Fase.pos += tamX;
				}
				printf("\n Fase PosX = %d", Fase.pos);
				
				if(Fase.pos < -2000)
				{
					Fase.pos = -2000;
				}
			}
			else
			{
				jogador.posX += jogador.velocidade;
			}
			/*
			printf("\n\nJogador PosX: %d", jogador.pos);
			printf("\nJogador Vel: %d", jogador.velocidade);
			printf("\nOponente PosX: %d", oponente.pos);
			printf("\nOponente Vel: %d", oponente.velocidade);
			*/
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
	void *R[2]; // Teste
	
	//Variaveis do jogo
	int gold = 0,
		FaseAtual = 0;
	
	StructCarro jogador,
		  		oponente;
		  
	StructFase Fase;
	
	Fase.pos = 0,
	Fase.comprimento = 15000;
	
	//Jogador
	jogador.pos = 0;
	jogador.posX = 0;
	jogador.aceleracao = 0;
	jogador.velocidade = 0;
	jogador.velocidadeMax = 0;
	
	jogador.motor = 1;
	jogador.turbo = 1;
	jogador.reducaoPeso = 1;
	jogador.injecao = 1;
	jogador.suspensao = 1;
	jogador.nitro = 1;
	jogador.pneu = 1;
	
	//Oponente
	oponente.pos = 0;
	oponente.posX = 0;
	oponente.aceleracao = 0;
	oponente.velocidade = 0;
	oponente.velocidadeMax = 0;
	
	oponente.motor = 1;
	oponente.turbo = 1;
	oponente.reducaoPeso = 1;
	oponente.injecao = 1;
	oponente.suspensao = 1;
	oponente.nitro = 1;
	oponente.pneu = 1;
	
	//Variaveis de controle
	int pg = 1,
		tamX = 1000,
		tamY = 600,
		FPS = 60,
		tamImagem = 0;
	
	char tecla = 0;
	unsigned long long gt1, gt2;
	
	//Variaveis dos menus
	int menuAtual = 0,
		menuAtual2 = 0;
	bool result = false;
	
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
	
	strcpy(Motor[MOTOR1].Nome, "1.8 AP Turbo 4 Cilindros");
	Motor[MOTOR1].Valor = 1;
	Motor[MOTOR1].Preco = 0;
	
	strcpy(Motor[MOTOR2].Nome, "2.0 4 Cilindros Forjado");
	Motor[MOTOR2].Valor = 3;
	Motor[MOTOR2].Preco = 100;
	
	strcpy(Motor[MOTOR3].Nome, "3.0 6 Cilindros em Linha 2JZ");
	Motor[MOTOR3].Valor = 5;
	Motor[MOTOR3].Preco = 300;
	
	//Turbos
	StructPecas Turbo[3];
	
	strcpy(Turbo[TURBO1].Nome, "Turbo Garret .42");
	Turbo[TURBO1].Valor = 1;
	Turbo[TURBO1].Preco = 0;
	
	strcpy(Turbo[TURBO2].Nome, "Turbo Garret .50");
	Turbo[TURBO2].Valor = 3;
	Turbo[TURBO2].Preco = 50;
	
	strcpy(Turbo[TURBO3].Nome, "Twin Turbo");
	Turbo[TURBO3].Valor = 5;
	Turbo[TURBO3].Preco = 100;
	
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
	Injecao[INJECAO2].Valor = 1;
	Injecao[INJECAO2].Preco = 50;
	
	strcpy(Injecao[INJECAO3].Nome, "Injeção Reprogramada");
	Injecao[INJECAO3].Valor = 1;
	Injecao[INJECAO3].Preco = 100;
	
	//Suspensores
	StructPecas Suspensao[3];
	
	strcpy(Suspensao[SUSPENSAO1].Nome, "Fixa");
	Suspensao[SUSPENSAO1].Valor = 1;
	Suspensao[SUSPENSAO1].Preco = 0;
	
	strcpy(Suspensao[SUSPENSAO2].Nome, "McPherson");
	Suspensao[SUSPENSAO2].Valor = 1;
	Suspensao[SUSPENSAO2].Preco = 50;
	
	strcpy(Suspensao[SUSPENSAO3].Nome, "Multilink");
	Suspensao[SUSPENSAO3].Valor = 1;
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
	Pneu[PNEU2].Valor = 3;
	Pneu[PNEU2].Preco = 50;
	
	strcpy(Pneu[PNEU3].Nome, "Pneus Profissionais");
	Pneu[PNEU3].Valor = 5;
	Pneu[PNEU3].Preco = 100;
	
	
	//Iniciar a janela do jogo ----------------------------------------------------------------------------------------------
	initwindow(tamX, tamY, "Click Tuning", 50, 50);
	
	tamImagem = imagesize(0,0,1000,600);
	R[0] = malloc(tamImagem);
	R[1] = malloc(tamImagem);
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000, 600);
	getimage(0, 0, 1000, 600, R[0]);
	readimagefile("Sprites/FundoTutorialeFase1Chegada.bmp", 0, 0, 1000, 600);
	getimage(0, 0, 1000, 600, R[1]);
	
	menuAtual = MENUPRINCIPAL;
	menuAtual = CUSTOMIZACAOCARRO;
	while(tecla != CR)
	{
		while(menuAtual == MENUPRINCIPAL)
		{
			//Alguma coisa
		}
		
		while(menuAtual == CUSTOMIZACAOCARRO)
		{
			gt2 = GetTickCount();
			if (gt2 - gt1 > 1000/FPS)
			{
				gt1 = gt2;
				
				if(pg == 1) pg = 2; else pg = 1;
				
				setactivepage(pg);
				setbkcolor(RGB(0,0,0));
				cleardevice();
				
				//Desenhos
				
				//Deixa a pagina visivel
				setvisualpage(pg);
				
				if(FaseAtual == 0)
				{
					oponente.velocidadeMax = 10;
					oponente.velocidade = 0;
					jogador.velocidade = 0;
					jogador.velocidadeMax = 100;
					jogador.posX = 0;
					oponente.posX = 0;
					result = iniciarCorrida(jogador, oponente, Fase, R, tamX, tamY);
					if (result){
						FaseAtual = 1;
						gold += 100;
					}
					else {
						FaseAtual = 0;
						gold += 50;
					}
				}
					
				setvisualpage(pg);
				
				tecla = 0;
				fflush(stdin);
				if (kbhit())
					tecla = getch ();
			}
		}
	}
	closegraph();
	return (0);
	
}
