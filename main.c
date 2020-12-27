//
// Created by Administrator on 2020/11/20.
//
// !!!charset encoding == "GBK";(sorry about that "UTF-8" made console Garbled code)
//
// C99 标准;
// 编译环境 mingw-w64-8.1.0 i686 x86_64 posix dwarf
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define RECAST_TIMES 888
#define CARDS_NUM 54
#define ONES_HADN_CARDS_NUM 12


/**
 * 初始化牌;
 */
void initMapper();

/**
 * 洗牌;
 */
void shuffle(void);

/**
 * 交换;
 * @param foo
 * @param bar
 */
void swap(int *foo, int *bar);

/**
 * 展示玩家手牌;
 * @param playerId
 */
void showHandCards(int playerId);

/**
 * 循环单元;
 */
void doLoop(void);

/**
 * 循环阻塞引擎;
 */
void start(void);


// 映射数组;
int mapper[CARDS_NUM] = {0};

enum cardColors
{
    CLUBS = 0, DIAMONDS, HEARTS, SPADES, JOKER
};

struct Card
{
    enum cardColors color;
    char value;
};

//static char cardValue[][2] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
static char cardValue[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};

static char colorString[][9] = {"Clubs", "Diamonds", "Hearts", "Spades", "Joker"};

static struct Card poker[CARDS_NUM];


/**
 * 初始化卡牌的字符串新皮肤;
 */
void initCardSkin()
{
    int i, j;
    enum cardColors color;
    for (i = 0; i <= 12; i++)
    {
        for (color = CLUBS; color <= SPADES; color++)
        {
            j = i * 4 + color;
            poker[j].color = color;
            poker[j].value = cardValue[i];
        }
    }

    // 生成大小王;
    color = JOKER;
    int k;
    for (k = 0; k < 2; ++k)
    {
        poker[52 + k].color = color;
        poker[52 + k].value = cardValue[k];
    }
}


/**
 * 初始化牌;
 */
void initMapper()
{
    int i;
    for (i = 0; i < CARDS_NUM; ++i)
    {
        mapper[i] = i;
    }
}

/**
 * 洗牌;
 */
void shuffle(void)
{
    srand(time(NULL));
    int rdm1, rdm2;
    int tmp;
    int i;
    for (i = 0; i < RECAST_TIMES; i++)
    {
        rdm1 = rand() % CARDS_NUM;
        rdm2 = rand() % CARDS_NUM;

        if (rdm1 != rdm2)
        {
            tmp = mapper[rdm1];
            mapper[rdm1] = mapper[rdm2];
            mapper[rdm2] = tmp;
        }
    }
}


/**
 * 交换;
 * @param foo
 * @param bar
 */
void swap(int *foo, int *bar)
{
    int *tmp = foo;
    *foo = *bar;
    *bar = *tmp;
}


/**
 * 展示玩家手牌, 现在把映射的mapper[i]作为index;
 * @param playerId
 */
void showHandCards(int playerId)
{
    int key;
    struct Card card;

    printf("玩家%d手牌有:\n", playerId);

    int i;
    for (i = playerId * ONES_HADN_CARDS_NUM; i < (playerId + 1) * ONES_HADN_CARDS_NUM; ++i)
    {
        key = mapper[i];
        card = poker[key];
        printf("%s_%c\t", colorString[card.color], card.value);
//        printf("%d", key);
    }
    printf("\n\n");
}


/**
 * 循环单元;
 */
void doLoop(void)
{
    printf("原牌序:\n");
    int i;
    for (i = 0; i < CARDS_NUM; ++i)
    {
        printf("%d\t", mapper[i]);
    }
    printf("\n现牌序:\n");
    shuffle();

    int j;
    for (j = 0; j < CARDS_NUM; ++j)
    {
        printf("%d\t", mapper[j]);
    }
    printf("\n");

    int k;
    for (k = 0; k < 4; ++k)
    {
        showHandCards(k);
    }

    printf("底牌有:\n");
    int l;
    int key;
    struct Card card;
    for (l = 6; l > 0; --l)
    {
        key = mapper[CARDS_NUM - l];
        card = poker[key];
        printf("%s_%c  ", colorString[card.color], card.value);
    }
    printf("其中0表示10\n\n");
}


/**
 * 循环阻塞引擎;
 */
void start(void)
{
    int choice;
    do
    {
        doLoop();
        printf("\n是否继续，任意输入继续，输入 0 退出:\n");
        scanf("%d", &choice);
        printf("\n");
    } while (choice);
}


int main()
{
    initMapper();
    initCardSkin();
    start();

    return 0;
}
