 //JOGNA2 - GRUPO 6

#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include <time.h>

#define LEFT   	75
#define RIGHT  	77
#define UP     	72
#define DOWN   	80
#define ESC     27

#define TECLAENTER		13
#define TECLABACKSPACE	8
#define CR	13

struct fase{
	long long int pos, comprimento;
};

struct carro1{
	long long int pos, velocidade, aceleracao, velocidadeMax;
};

struct carromaquina{
	long long int pos, velocidade, aceleracao, velocidadeMax;
};

carro1 jogador;
fase fase1;
carromaquina oponente;
int velocidade, tamX, tamY, FPS, tam, gold;
int FaseAtual, LimiteFase;
void *R;
int pg = 1;
unsigned long long gt1, gt2;
bool result;


bool fase(int comprimento){
	bool resultado;
	
	jogador.pos = fase1.pos;
	jogador.aceleracao = 5;
	oponente.aceleracao = 0;
	oponente.pos =0;
	oponente.velocidade = 0;
	
	while (jogador.pos <= comprimento){
		
		printf("Funcao fase\n");
		/*gt2 = GetTickCount();
		gt1 = gt2;
		if (gt2 - gt1 > 1000/FPS){
			gt2 = gt1;*/
			
			if(pg == 1) pg = 2; else pg = 1;
			setactivepage(pg);
			gt1 = GetTickCount();
			setbkcolor(RGB(0,0,0));
			cleardevice();
		
			//Movimentação do jogador
			//jogador.velocidade = 0;
			if(jogador.velocidadeMax >= jogador.velocidade){
			
				if(GetAsyncKeyState(VK_RIGHT)&0x0080) {
					jogador.velocidade += jogador.aceleracao;
					printf("suhaush");
				}
			      	
			    else if(GetAsyncKeyState(VK_SPACE)&0x0080)
			      	jogador.velocidade += jogador.aceleracao*5;
			    else if(GetAsyncKeyState(VK_LEFT)&0x0080)
			      	jogador.velocidade -= jogador.aceleracao*5;
			}

		      	
		    jogador.pos += jogador.velocidade;
			fase1.pos -= jogador.velocidade;
			
			if(oponente.velocidade <= oponente.velocidadeMax){
				oponente.velocidade += oponente.aceleracao;
			}
			oponente.pos += oponente.velocidade;
			printf("%d", oponente.pos);
					
			//Desenhar a fase
			putimage(fase1.pos, 0, R, COPY_PUT);
			putimage(fase1.pos-tamX, 0, R, COPY_PUT);
			putimage(fase1.pos+tamX, 0, R, COPY_PUT);
			if(fase1.pos <= -tamX || fase1.pos >= tamX ){
				fase1.pos = 0;	
			}
			
			setfillstyle(1,RGB(0,255,0));
			bar(jogador.pos+50,520,jogador.pos+100,570);
			setfillstyle(1,RGB(255,0,0));
			bar(oponente.pos+50,400,oponente.pos+100,450);
			setvisualpage(pg);
			do{
				gt2 = GetTickCount(); 
			}while(gt2 - gt1 > 1000/FPS);
			
	}
	if (jogador.pos >= comprimento && oponente.pos < comprimento){ //Ganhou
		resultado = true;
	}
	else if ((jogador.pos < comprimento && oponente.pos >= comprimento) || (jogador.pos = comprimento && oponente.pos >= comprimento )){ //Perdeu
		resultado = false;
	}

	
	return(resultado);
}

<<<<<<< HEAD
int main(){
=======
int main()
{	
	//Imagens
	void *R[3]; // Teste
	
	//Variaveis do jogo
	int gold = 0,
		FaseAtual = 0;
>>>>>>> 3e751f23ac57e7d98b0cb8f73d6995e4f3e578cc
	
	jogador.pos = 0;
<<<<<<< HEAD
	fase1.comprimento = 15000;
	tamX = 1000;
	tamY = 600;
	
	initwindow(tamX, tamY, "Click Tuning", 50, 50);
=======
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
		tamImagem = 0,
		i = 0,
		Selecao = 0;
	
	char tecla = 0,
		 Texto[50],
		 Texto2[50];
	unsigned long long gt1, gt2;
	
	//Variaveis dos menus
	int menuAtual = 0,
		menuAtual2 = 0;
	bool result = false;
	
	int Menu1PosX = 60,
		Menu1PosY = 190,
		Menu1PosYD = 45;
	
	//Ponteiros --------------------------------------------------------------------
	int ListaMotoresTamanho = 3,
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
	//ListaMotores[ListaMotoresTamanho - 1] = MOTOR1;
	ListaMotores[0] = MOTOR1;
	ListaMotores[1] = MOTOR2;
	ListaMotores[2] = MOTOR3;
	
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
	Motor[MOTOR2].Preco = 100;
	
	strcpy(Motor[MOTOR3].Nome, "3.0 - 6 Cilindros em Linha 2JZ");
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
>>>>>>> 3e751f23ac57e7d98b0cb8f73d6995e4f3e578cc
	
	char tecla;
	
	FaseAtual = 0;
	gold = 0;
	tecla = 0;
	velocidade = 0;
	FPS = 60;
	tam = imagesize(0,0,1000,600);
	R = malloc(tam);
	
<<<<<<< HEAD
	fase1.pos = 0;
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000, 600);
	getimage(0, 0, 1000, 600, R);
	cleardevice();
	while(tecla != CR) {
		printf("Entrei\n");
		if(FaseAtual == 0){
			oponente.velocidadeMax = 10;
			jogador.velocidadeMax = 100;
			printf("Aqui\n");
			result = fase(1500000);
			if (result){
				FaseAtual = 1;
				gold += 100;
			}
			else {
				FaseAtual = 0;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 1){
			oponente.velocidadeMax = 50;
			jogador.velocidadeMax = 100;
			result = fase(10000);
			if (result){
				FaseAtual = 2;
				gold += 100;
			}
			else {
				FaseAtual = 1;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 2){
			oponente.velocidadeMax = 75;
			jogador.velocidadeMax = 100;
			result = fase(15000);
			if (result){
				FaseAtual = 3;
				gold += 100;
			}
			else {
				FaseAtual = 2;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 3){
			oponente.velocidadeMax = 95;
			jogador.velocidadeMax = 100;
			if (fase(15000)){
				FaseAtual = 4;
				gold += 400;
=======
	tamImagem = imagesize(0, 0, 1000 - 1, 600 - 1);
	R[0] = malloc(tamImagem);
	R[1] = malloc(tamImagem);
	R[2] = malloc(imagesize(0, 0, 335 - 1, 45 - 1));
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, R[0]);
	readimagefile("Sprites/FundoTutorialeFase1Chegada.bmp", 0, 0, 1000 - 1, 600 - 1);
	getimage(0, 0, 1000 - 1, 600 - 1, R[1]);
	readimagefile("Sprites/menuCustomizacao1.bmp", 0, 0, 335 - 1, 45 - 1);
	getimage(0, 0, 335 - 1, 45 - 1, R[2]);
	
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
				setbkcolor(RGB(230, 230, 230));
				cleardevice();
				
				//Desenhos
				
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
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
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
					}
					
					setcolor(RGB(30, 30, 200));
					setlinestyle(0, 0, 3);
					rectangle(Menu1PosX, Menu1PosY + (Menu1PosYD * Selecao), Menu1PosX + 335, Menu1PosY + 45 + (Menu1PosYD * Selecao));
				}
				
				//Deixa a pagina visivel
				setvisualpage(pg);
				
				//Acoes
				if(tecla == RIGHT)
				{
					menuAtual2 ++;
					Selecao = 0;
					if(menuAtual2 > 6)
					{
						menuAtual2 = 0;
					}
				}
				if(tecla == LEFT)
				{
					menuAtual2 --;
					Selecao = 0;
					if(menuAtual2 < 0)
					{
						menuAtual2 = 6;
					}
				}
				
				if(menuAtual2 == MENUMOTOR)
				{
					if(tecla == UP && Selecao > 0)
					{
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaMotoresTamanho - 1)
					{
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						jogador.motor = Motor[ListaMotores[Selecao]].Valor;
						printf("\nMotor: %d", jogador.motor);
					}
				}
				
				if(menuAtual2 == MENUTURBO)
				{
					if(tecla == UP && Selecao > 0)
					{
						Selecao --;
					}
					if(tecla == DOWN && Selecao < ListaTurbosTamanho - 1)
					{
						Selecao ++;
					}
					if(tecla == TECLAENTER)
					{
						jogador.turbo = Turbo[ListaTurbos[Selecao]].Valor;
						printf("\nTurbo: %d", jogador.turbo);
					}
				}
				
				/*
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
				*/
				
				tecla = 0;
				fflush(stdin);
				if (kbhit())
				{
					tecla = getch ();
				}
>>>>>>> 3e751f23ac57e7d98b0cb8f73d6995e4f3e578cc
			}
			else {
				FaseAtual = 3;
				gold += 50;
			}	
		}
			
		printf("%d\n", jogador.pos);
				
		/*if(jogador.pos > fase1.comprimento){
			printf("Voce ganhou\n");
		}*/
			
		//delay(50);
			
		setvisualpage(pg);
			
		fflush(stdin);
		if (kbhit())
			tecla = getch ();
	
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
