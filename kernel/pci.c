#include <norby/pci.h>
#include <stdint.h>
#include <sys/io.h>

enum pci_class_code {
  PCI_CLASS_OLD_DEVICE = 0x00,
  PCI_CLASS_MASS_STORAGE_CONTROLLER = 0x01,
  PCI_CLASS_NETWORK_CONTROLLER = 0x02,
  PCI_CLASS_DISPLAY_CONTROLLER = 0x03,
  PCI_CLASS_MULTIMEDIA_CONTROLLER = 0x04,
  PCI_CLASS_MEMORY_CONTROLLER = 0x05,
  PCI_CLASS_BRIDGE_DEVICE = 0x06,
  PCI_CLASS_SIMPLE_COMMUNICATION_CONTROLLER = 0x07,
  PCI_CLASS_BASE_SYSTEM_PERIPHERAL = 0x08,
  PCI_CLASS_INPUT_DEVICE = 0x09,
  PCI_CLASS_DOCKING_STATION = 0x0A,
  PCI_CLASS_PROCESSOR = 0x0B,
  PCI_CLASS_SERIAL_BUS_CONTROLLER = 0x0C,
  PCI_CLASS_WIRELESS_CONTROLLER = 0x0D,
  PCI_CLASS_INTELLIGENT_IO_CONTROLLER = 0x0E,
  PCI_CLASS_SATELLITE_COMMUNICATION_CONTROLLER = 0x0F,
  PCI_CLASS_ENCRYPTION_DECRYPTION_CONTROLLER = 0x10,
  PCI_CLASS_DATA_ACQUISITION_OR_SIGNAL_PROCESSING_CONTROLLER = 0x11,
  /* ..and a whole bunch of reserved codes... (0x12-0xFE) */
  PCI_CLASS_NO_DEFINED_CLASS = 0xFF,
};

//struct pci_device {};

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func,
                              uint8_t offset) {
  uint32_t address;
  uint32_t lbus = (uint32_t) bus;
  uint32_t lslot = (uint32_t) slot;
  uint32_t lfunc = (uint32_t) func;
  uint16_t temp = 0;

  address = (uint32_t)
    ( (lbus << 16)
    | (lslot << 11)
    | (lfunc << 8)
    | (offset & 0xFC)
    | ((uint32_t) 0x80000000)
    );
  outl(PCI_CONFIG_ADDRESS, address);
  temp = (uint16_t) ((inl(PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xFFFF);
  return temp;
}

uint16_t pci_check_vendor(uint8_t bus, uint8_t slot) {
  uint16_t vendor;
  uint16_t device;
  if((vendor = pci_config_read_word(bus, slot, 0, 0)) != 0xFFFF) {
    device = pci_config_read_word(bus, slot, 0, 2);
  }
  return (vendor);
}
