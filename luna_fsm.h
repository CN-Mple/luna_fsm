/* luna_fsm.h */
#ifndef LUNA_FSM_H
#define LUNA_FSM_H

#include <stdint.h>

#ifndef LUNA_FSM_ASSERT
#define LUNA_FSM_ASSERT(expr) ((void)0)
#endif

#define HANDLED		(uint32_t)(0)
#define IGNORED		(uint32_t)(1)
#define TRANSFER	(uint32_t)(2)

#define HAND()		HANDLED
#define IGNO()		IGNORED
#define TRAN(t) \
			me->handler = t, TRANSFER

struct luna_evt {
    uint16_t sig;
};

struct luna_fsm;

typedef uint32_t (*luna_fsm_handler_t)(struct luna_fsm *fsm, const struct luna_evt *evt);

struct luna_fsm {
	luna_fsm_handler_t handler;
};

enum {
	SIG_EMPTY = 0,
	SIG_ENTER,
	SIG_EXIT,
	SIG_INIT,
	SIG_INTERRUPT,
	SIG_RESERVE_SIG_NUM,
	CUSTOM_SIG = SIG_RESERVE_SIG_NUM,
};

void luna_fsm_init(struct luna_fsm *me);
void luna_fsm_dispatch(struct luna_fsm *me, const struct luna_evt *evt);

#endif
