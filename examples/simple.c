#include <carp/carp.h>

int main (int argc, char **argv) {
  char data[][CARP_HT_KEY_LENGTH] = {
    "hello",
    "world"
  };

  // I wish there was a better way to do this.
  long long hellop = (long long) &data[0];

  long long code[] = {
    // 3 + 9 + 7 == 19?
    CARP_INSTR_LOAD,  CARP_REG0, 7,
    CARP_INSTR_PREG,  CARP_REG0,
    CARP_INSTR_PUSH,  3,
    CARP_INSTR_PUSH,  9,
    CARP_INSTR_ADD,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSHR, CARP_REG0,
    CARP_INSTR_ADD,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSH,  19,
    CARP_INSTR_CMP,
    CARP_INSTR_PREG,  CARP_EAX,

    // set & get 20
    CARP_INSTR_DBS,   hellop, 20,
    CARP_INSTR_DBG,   hellop, CARP_EAX,
    CARP_INSTR_PREG,  CARP_EAX,
    
    // should be in $?
    CARP_INSTR_HALT, 1
  };

  carp_machine_state m;
  carp_vm_init(&m, 10, 0);
  carp_vm_load(&m, code);
  carp_vm_run(&m);
}
