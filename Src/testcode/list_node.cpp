#include <stdint.h>
#include <stdlib.h>

#include "test_config.h"
#include "CppUTest/TestHarness.h"

typedef struct tagListNode {
	struct tagListNode *prev;
	struct tagListNode *next;
	uint32_t data;
} ListNode;

static const uint32_t data_512byte_0[TEST_DATA_512BYTE]={
  0xb8d0f8caul,0x36d42d43ul,0x96e6c5a0ul,0x515d7e4aul,0x7baba99eul,0x0d489ce3ul,0xa33b9776ul,0xcaa4718ful,
  0x974642fbul,0xaee916c9ul,0xdce4d3c3ul,0x4cdeb1c9ul,0x50270000ul,0xc5120538ul,0x169de503ul,0x5e13b11cul,
  0x1ccbb520ul,0x5dc4f289ul,0xa79afb79ul,0xd39694caul,0xd94b2d9cul,0x43ab3cccul,0x48752af2ul,0xf4df92cbul,
  0xf8b8eb64ul,0x299f453cul,0x6ce2a1bdul,0xf4b2a956ul,0x20e70652ul,0x04feb89bul,0x2fce599dul,0x5efbcec6ul,
  0xbc9b3963ul,0xa41355a3ul,0xbc9963daul,0x55602a85ul,0x516a5cabul,0x75df03dbul,0xffec9a3cul,0x566036acul,
  0x33fa188bul,0x060d5226ul,0x43b81875ul,0xc7170f47ul,0xc553fcadul,0x4543397eul,0x8e92b20ful,0x01313863ul,
  0x23ab8f5eul,0xed97cbfeul,0x17cb8587ul,0x752f16f1ul,0x78cafdc5ul,0x663258edul,0x66e8322aul,0xbac15193ul,
  0x9d04a062ul,0xac81ebc2ul,0xd5a445daul,0xcee93501ul,0x16723868ul,0xa964cfa3ul,0x1f5e45f6ul,0x2a6564a2ul,
  0x57ba44cdul,0x88b6937bul,0x73523c10ul,0x2e4beee6ul,0xa67a2387ul,0x5a211530ul,0x44f1aa2dul,0x3af4313cul,
  0x1868ee2aul,0xf759fa24ul,0x3c19a02bul,0x87c630e3ul,0xe31c9fbeul,0xa24cd7feul,0xfc612bcaul,0xd43dec65ul,
  0x4d03271bul,0xc0c7806cul,0x6cc5e0e0ul,0xc59ef1b8ul,0xbd12e9b7ul,0x9e7ab5f1ul,0x0632a549ul,0x8870e840ul,
  0xb0e70106ul,0x58d2c177ul,0x56161febul,0xbad524c1ul,0x2df60e9cul,0xeedc0c41ul,0x0cc7581bul,0x26eab189ul,
  0xd0dec84aul,0xa36788d8ul,0x86688b8bul,0xb72ffae2ul,0x629272a3ul,0x7ab353aeul,0xc96d5b61ul,0x9cd9f349ul,
  0x57ef749cul,0x513095c4ul,0xd415c18cul,0xf2750354ul,0xa83b12a0ul,0x2dcab815ul,0xade84045ul,0xea058bb2ul,
  0xd099e198ul,0xdef48083ul,0xf38a594bul,0xa5fac9fful,0xaa5d3115ul,0x0b3d58a1ul,0xfd3cc574ul,0xf8648407ul,
  0xc3bf00f2ul,0xca0ed06bul,0x3f803024ul,0xe6a743eeul,0x4d92df70ul,0xa1f23d3ful,0x5c31d752ul,0x6e41b303ul};


TEST_GROUP(list_node)
{
  void setup() { }
  void teardown() { }
};

TEST(list_node, treeTest)
{
	uint32_t i;
	uint64_t sum;

	ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;

  firstnode = lastnode = NULL;
  for (i = 0; i < TEST_DATA_512BYTE; i++) {
    newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->data = data_512byte_0[i];
    newnode->next = NULL;
    if (lastnode != NULL)
    {
      lastnode->next = newnode;
      newnode->prev = lastnode;
      lastnode = newnode;
    }
    else
    {
      firstnode = lastnode = newnode;
      newnode->prev = NULL;
    }
  }
  sum = 0;
  for (thisnode = firstnode; thisnode != NULL;thisnode = thisnode->next)
  {
    sum += thisnode->data;
  }
  for (thisnode = firstnode; thisnode != NULL;)
  {
    removenode = thisnode;
    thisnode = thisnode->next;
    free(removenode);
  }
  CHECK_EQUAL(0x000000424E565018ull, sum);
}