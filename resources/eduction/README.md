# Eduction Lessons Resources

Various resource folders & files used by the Eduction lessons.

---

- [PCI](#pci)
  - [`account_nbr`](#account_nbr)
  - [`pci_all`](#pci_all)
  - [`redact_account_nbr`](#redact_account_nbr)
- [PHI](#phi)
  - [`phi_all`](#phi_all)
- [PII](#pii)
  - [`pii_address`](#pii_address)
  - [`pii_table_mode`](#pii_table_mode)
  - [`custom_pp_threshold`](#custom_pp_threshold)
  - [`custom_validation`](#custom_validation)
- [SDK](#sdk)

---

## PCI

### `account_nbr`

Contains Eduction configuration file and input text to explore PCI PAN (aka `account_nbr`) entity.

### `pci_all`

Contains Eduction configuration file and input text with valid matches for all PCI entity categories.

### `redact_account_nbr`

Contains Eduction configuration file, input text and Lua script to redact detected PCI PAN (aka `account_nbr`) entities.

## PHI

### `phi_all`

Contains Eduction configuration file and input text with valid matches for all PHI entity categories.

## PII

### `pii_address`

Contains Eduction configuration file and input text to explore postal address detection (aka `pii_address`) entity.

### `pii_table_mode`

Contains Eduction configuration file, input text and more to use table structure to help identify PII entities.

### `custom_pp_threshold`

Contains Eduction configuration file, input text and script implementing an entity specific post-process threshold. Used with the custom post-processing lesson.

### `custom_validation`

Contains Eduction configuration file, input text and script implementing match-window post-process. Used with the custom post-processing lesson.

## SDK

Contains helper files to accompany lessons on compiling sample code in C, Java, .NET and Python.
