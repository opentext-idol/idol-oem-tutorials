# IDOL ACI APIs

This track of the IDOL OEM tutorials is focussed on IDOL's ACI API.  

Below are links to lessons, which will take you through an introduction to the ACI API, exploration of advanced features, as well as ways to use IDOL Eduction in your environment.

---

- [Introduction](#introduction)
- [Capability showcase](#capability-showcase)
  - [Use IDOL Eduction Server](#use-idol-eduction-server)
  - [Perform file actions using the IDOL Dropbox Connector](#perform-file-actions-using-the-idol-dropbox-connector)

---

## Introduction

The IDOL (Intelligent Data Operating Layer) platform includes a suite of components (services), which can be used in combination or alone to perform hundreds of useful functions, including the Eduction and KeyView filtering that you have become familiar with in previous lessons.

Each IDOL service supports a REST-style API, called the ACI (Autonomy Content Infrastructure) Client API, which allows client applications to perform the following, but not limited to, types of functions:

- monitor the service status
- perform administrative actions
- load data into the service
- train the models of the service
- ask service to perform analytics on data

The ACI Client API can be implemented directly using HTTP requests for non-OEM licensed client applications.  However, for OEM-licensed applications, the SDK must be used.

The ACI Client API SDK is currently available for C, Java and .NET.

[Get started](./introduction.md).

## Capability showcase

Do more with the IDOL ACI API.

> NOTE: This guide assumes you have already completed the introductory IDOL ACI API lesson above.

### Use IDOL Eduction Server

Perform Eduction as a service by calling the IDOL Eduction Server using the IDOL ACI API.

[Get started](../eduction/eduction_server.md).

### Perform file actions using the IDOL Dropbox Connector

Set up a Dropbox application and use Python to invoke the IDOL Connector Fetch API to list, collect, delete and insert files into your Dropbox account.

[Get started](./dropbox_connector.md).

---

Next, why not try more tutorials to explore some of the other features available in IDOL, linked from the [main](../README.md#capability-showcase-examples) page.
