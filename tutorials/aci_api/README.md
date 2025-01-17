# ACI APIs

This track of the OEM tutorials is focussed on the ACI API.  

Below are links to lessons, which will take you through an introduction to the ACI API, exploration of advanced features, as well as example usage of the API to control various Knowledge Discovery services.

---

- [Introduction](#introduction)
- [Capability showcase](#capability-showcase)
  - [Use Eduction Server](#use-eduction-server)
  - [Perform file actions using the Dropbox Connector](#perform-file-actions-using-the-dropbox-connector)

---

## Introduction

The OpenText Knowledge Discovery platform includes a suite of components (services), which can be used in combination or alone to perform hundreds of useful functions, including the Eduction and File Content Extraction that you have become familiar with across previous lessons.

Each Knowledge Discovery service supports a REST-style API, called the ACI (Autonomy Content Infrastructure) Client API, which allows client applications to perform the following, but not limited to, types of functions:

- monitor the service status
- perform administrative actions
- load data into the service
- train the models of the service
- ask service to perform analytics on data

The ACI Client API can be implemented directly using HTTP requests for non-OEM licensed client applications.  However, for OEM-licensed applications, the SDK must be used.

The ACI Client API SDK is currently available for C, Java and .NET.

[Get started](./introduction.md).

## Capability showcase

Do more with the ACI API.

> NOTE: This guide assumes you have already completed the introductory ACI API lesson above.

### Use Eduction Server

Perform Eduction as a service by calling the Eduction Server using the ACI API.

[Get started](../eduction/eduction_server.md).

### Perform file actions using the Dropbox Connector

Set up a Dropbox application and use Python to invoke the Connector Fetch API to list, collect, delete and insert files into your Dropbox account.

[Get started](./dropbox_connector.md).

---

Next, why not try more tutorials to explore some of the other features available in Knowledge Discovery, linked from the [main](../README.md#capability-showcase-examples) page.
