/* luna_fsm.c */
#include "luna_fsm.h"

static const struct luna_fsm_evt luna_fsm_reserve_sigs[] = {
	{.sig = EMPTY_SIG},
	{.sig = ENTER_SIG},
	{.sig = EXIT_SIG},
	{.sig = INIT_SIG},
};

void luna_fsm_ctor(struct luna_fsm *me, luna_fsm_handler_t handler)
{
	me->handler = handler;
}

void luna_fsm_init(struct luna_fsm *me, struct luna_fsm_evt const *evt)
{
	LUNA_FSM_ASSERT(me);
	LUNA_FSM_ASSERT(me->handler);

	(void)(*me->handler)(me, evt);
	(void)(*me->handler)(me, &luna_fsm_reserve_sigs[ENTER_SIG]);
}

void luna_fsm_dispatch(struct luna_fsm *me, struct luna_fsm_evt const *evt)
{
	LUNA_FSM_ASSERT(me);
	LUNA_FSM_ASSERT(evt);
	LUNA_FSM_ASSERT(me->handler != 0);

	luna_fsm_handler_t handler = me->handler;
	uint32_t rt = (*handler)(me, evt);
	if (RET_TRANSFER == rt) {
		(void)(*handler)(me, &luna_fsm_reserve_sigs[EXIT_SIG]);
		(void)(*me->handler)(me, &luna_fsm_reserve_sigs[ENTER_SIG]);
	}
}
