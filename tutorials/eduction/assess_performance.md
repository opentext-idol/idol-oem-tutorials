# Assessing Performance of Eduction

IDOL Eduction includes multiple tools to assess the performance of matching.  `edktool` has benchmark, assess and measure to aid in assessing processing speed and match efficacy.

In this lesson, you will:
- Explore tools to measure processing speed.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](./introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
- [Running `edktool` extract](#running-edktool-extract)
- [Running edktool benchmark](#running-edktool-benchmark)
- [Optimizations](#optimizations)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](./introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

## Running `edktool` extract

Run the following commands to see the output:

```sh
cd C:\OpenText\EductionSDK_23.2.0_WINDOWS_X86_64\samples\eduction_from_config\resources
edktool extract -l ..\..\..\licensekey.dat -c test\config\test.cfg -i test\input\input.txt -o out.xml
```

The output will contain the following related to processing time:

```
Successfully configured 1 post-processing tasks.
Beginning engine initialization (T+0.015 seconds)

...

Eduction initialized (T+0.078 seconds)
Opening data file...
Entity search completed (T+0.078 seconds)

0.078 seconds elapsed
```

The `T+#.### seconds` reflects elapsed time. The elapsed times are output at the beginning of EDKEngine initialization, after EDKEngine initialization (EDKSession begin) and after the input file is processed. 

For real world applications, it is a best practice to persist the EDKEngine across documents, only creating/destroying the EDKSession per document. Therefore, it's the EDKSession time that is most interest and variable per input file. A simple subtraction `Beginning engine initialization` - `Eduction initialized` results in the processing time for EDKEngine initialization.  A simple subtraction `Eduction initialized` - `Entity search completed` results in the processing time for scanning the input file.

> NOTE: The EDKEngine initialization time is proportional to the number and size of the grammars (or ResourceFiles) that are configured.

> NOTE: The EDKSession or entity search time is influenced by the EDKEngine settings (e.g. resource files (ECRs), entities enabled, other configuration settings), the size of the input file and the number of matches. 

> NOTE: As of 23.2.0 `edktool` reads the entire file and submits that as text rather than using the EDK streaming input APIs. The edk_samples\eduction_from_config can be instrumented to measure processing speed that reflects use of the streaming input APIs.

## Running edktool benchmark

Run the following commands to see the output:

```
cd C:\OpenText\EductionSDK_23.2.0_WINDOWS_X86_64\samples\eduction_from_config\resources
edktool benchmark -l ..\..\..\licensekey.dat -c test\config\test.cfg -i test\input\input.txt -s 3 -n 5
```

The key setting `-s 1` means one EDKSession (or thread) is run. The other key setting `-n 5` runs the same document 5 times in order to avoid any transient anomalies that may influence processing speed.  The individual iterations & threads are output along with an overall timing summary.

```
Iteration 0 produced the following results:
        Process 0 produced 2 matches in 0.003 seconds.
        Process 1 produced 2 matches in 0.003 seconds.
        Process 2 produced 2 matches in 0.003 seconds.
Iteration 0 took 0.006 seconds to complete.
Iteration 1 produced the following results:
        Process 0 produced 2 matches in 0.003 seconds.
        Process 1 produced 2 matches in 0.003 seconds.
        Process 2 produced 2 matches in 0.003 seconds.
Iteration 1 took 0.005 seconds to complete.
Iteration 2 produced the following results:
        Process 0 produced 2 matches in 0.003 seconds.
        Process 1 produced 2 matches in 0.003 seconds.
        Process 2 produced 2 matches in 0.003 seconds.
Iteration 2 took 0.008 seconds to complete.
Iteration 3 produced the following results:
        Process 0 produced 2 matches in 0.002 seconds.
        Process 1 produced 2 matches in 0.002 seconds.
        Process 2 produced 2 matches in 0.002 seconds.
Iteration 3 took 0.005 seconds to complete.
Iteration 4 produced the following results:
        Process 0 produced 2 matches in 0.003 seconds.
        Process 1 produced 2 matches in 0.003 seconds.
        Process 2 produced 2 matches in 0.003 seconds.
Iteration 4 took 0.006 seconds to complete.
Session timing summary:
        Observations: 15
        Mean: 0.0028s
        Min: 0.002s
        Max: 0.003s
        Standard deviation: 0.0004s

0.064 seconds elapsed
```

> NOTE: The input file and EDK configuration are simple in this example, resulting in iterations that sometimes complete in effectively zero time.

> NOTE: In `edktool benchmark` the match output as you've experienced with `edktool extract` is disabled by default. Adding `-d` will output simple match information.

## Optimizations

Besides simplifying your configuration or getting a faster computer, there some settings that can impact performance. 

For processing speed, here's some things to consider:
- use a pre-filter.  See [here](https://www.microfocus.com/documentation/idol/IDOL_23_2/EductionSDK_23.2_Documentation/Guides/html/Content/UseEduction/PreFiltering/PreFiltering.htm) for more details.
- set EntityMatchLimitN - See [here](https://www.microfocus.com/documentation/idol/IDOL_23_2/EductionSDK_23.2_Documentation/Guides/html/Content/Configuration/Eduction/_EDU_EntityMatchLimitN.htm) for more details.  In some applications, the existence of enough matches per each configured entity can be sufficient to take action based on the detected matches.
- For the PII, PHI, PCI grammars disable output normalization.  The name, address and date entities have output normalization enabled by default. See `scripts\names_stoplist.lua`, `scripts\address_stoplist.lua` and `scripts\normalize_date.lua` for details on how to configure.  Over enough matches (e.g tens vs thousands) the extra time to produce normalized output adds up.  Only some applications (e.g. searching on matches across a set of indexed documents) benefit normalized output.

## Conclusion

You now understand how to assess performance of Eduction.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#capability-showcase-examples).

## See also

- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_2/EductionSDK_23.2_Documentation/Guides/html/)
- [IDOL Release Notes](https://www.microfocus.com/documentation/idol/IDOL_23_2/IDOLReleaseNotes_23.2_Documentation/idol/Content/SDKs/Eduction.htm)
