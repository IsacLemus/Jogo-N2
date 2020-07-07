 //JOGNA2 - GRUPO 6

#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include <time.h>

#define CR	13

struct Fase{
	int pos, comprimento;
};

struct carro1{
	int pos, posX, velocidade, aceleracao, velocidadeMax;
};

struct carromaquina{
	int pos, posX, velocidade, aceleracao, velocidadeMax;
};

bool fase(int comprimento, carro1 jogador, carromaquina oponente, Fase fase1, void *R[], int tamX, int tamY){
	bool resultado;
	
	int pg = 1;
	unsigned long long gt1, gt2;
	int FPS = 60;
	
	jogador.pos = fase1.pos;
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
			putimage(fase1.pos, 0, R[0], COPY_PUT);
			putimage(fase1.pos+tamX, 0, R[0], COPY_PUT);
			putimage(fase1.pos+(tamX*2), 0, R[1], COPY_PUT);
			
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
			oponente.pos += oponente.velocidade;
			oponente.posX += oponente.velocidade;
		    
		    jogador.pos += jogador.velocidade;
			
			if((jogador.posX > tamX / 3) && (fase1.pos > -2000))
			{
				fase1.pos -= jogador.velocidade;
				oponente.posX -= jogador.velocidade;
				if((fase1.pos < -(tamX)) && ((comprimento - jogador.pos) > 2000))
				{
					fase1.pos += tamX;
				}
				printf("\n Fase PosX = %d", fase1.pos);
				
				if(fase1.pos < -2000)
				{
					fase1.pos = -2000;
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
	if (jogador.pos >= comprimento && oponente.pos < comprimento){ //Ganhou
		resultado = true;
	}
	else if ((jogador.pos < comprimento && oponente.pos >= comprimento) || (jogador.pos = comprimento && oponente.pos >= comprimento )){ //Perdeu
		resultado = false;
	}

	
	return(resultado);
}

int main(){
	
	carro1 jogador;
	carromaquina oponente;
	Fase fase1;
	
	int velocidade, tamX, tamY, FPS, tam, gold;
	int FaseAtual, LimiteFase;
	void *R[2];
	int pg = 1;
	unsigned long long gt1, gt2;
	bool result;
	
	tamX = 1000;
	tamY = 600;
	
	initwindow(tamX, tamY, "Click Tuning", 50, 50);
	
	jogador.pos = 0;
	fase1.comprimento = 15000;
	
	char tecla;
	
	FaseAtual = 0;
	gold = 0;
	tecla = 0;
	velocidade = 0;
	FPS = 60;
	tam = imagesize(0,0,1000,600);
	R[0] = malloc(tam);
	R[1] = malloc(tam);
	
	fase1.pos = 0;
	
	readimagefile("Sprites/FundoTutorialeFase1.bmp", 0, 0, 1000, 600);
	getimage(0, 0, 1000, 600, R[0]);
	readimagefile("Sprites/FundoTutorialeFase1Chegada.bmp", 0, 0, 1000, 600);
	getimage(0, 0, 1000, 600, R[1]);
	cleardevice();
	while(tecla != CR) {
		printf("Entrei\n");
		if(FaseAtual == 0){
			oponente.velocidadeMax = 10;
			oponente.velocidade = 0;
			jogador.velocidade = 0;
			jogador.velocidadeMax = 100;
			jogador.posX = 0;
			oponente.posX = 0;
			printf("Aqui\n");
			result = fase(15000, jogador, oponente, fase1, R, tamX, tamY);
			if (result){
				FaseAtual = 1;
				gold += 100;
			}
			else {
				FaseAtual = 0;
				gold += 50;
			}	
		}
		
		/*	
		if(FaseAtual == 1){
			oponente.velocidadeMax = 50;
			jogador.velocidadeMax = 100;
			//result = fase(10000);
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
			//result = fase(15000);
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
			}
			else {
				FaseAtual = 3;
				gold += 50;
			}	
		}
		*/
			
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
	closegraph();
	return (0);
	
}
