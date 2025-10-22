# Assessing Performance of Named Entity Recognition

Named Entity Recognition includes multiple tools to assess the performance of matching.  `edktool` has benchmark, assess and measure to aid in assessing processing speed and match efficacy.

In this lesson, you will:

- Explore tools to measure processing speed.
- Explore tools to measure match quality.

> NOTE: This guide assumes you have already completed the introductory Named Entity Recognition [tutorial](./introduction.md).

---

- [Setup](#setup)
- [Performance - Speed](#performance---speed)
  - [Running `edktool` extract](#running-edktool-extract)
  - [Running edktool benchmark](#running-edktool-benchmark)
- [Performance - Match Quality](#performance---match-quality)
  - [Running edktool measure](#running-edktool-measure)
- [Optimizing Performance](#optimizing-performance)
  - [Speed](#speed)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Named Entity Recognition SDK introduction](./introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Named Entity Recognition concepts.

## Performance - Speed

### Running `edktool` extract

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples\eduction_from_config\resources
> edktool.exe extract -l ..\..\..\licensekey.dat -c test\config\test.cfg -i test\input\input.txt -o out.xml
```

The output will contain the following related to processing time:

```txt
Successfully configured 1 post-processing tasks.
Beginning engine initialization (T+0.015 seconds)

...

Eduction initialized (T+0.078 seconds)
Opening data file...
Entity search completed (T+0.078 seconds)

0.078 seconds elapsed
```

The `(T+#.### seconds)` reflects elapsed time. The elapsed times are output at the beginning of EDKEngine initialization, after EDKEngine initialization (EDKSession begin) and after the input file is processed.

For real world applications, it is a best practice to persist the EDKEngine across documents, only creating/destroying the EDKSession per document. Therefore, it's the EDKSession time that is of most interest and variable per input file. A simple subtraction `Beginning engine initialization` - `Eduction initialized` yields the processing time for EDKEngine initialization.  A simple subtraction `Eduction initialized` - `Entity search completed` yields the processing time for scanning the input file.

> NOTE: The EDKEngine initialization time is proportional to the number and size of the grammars (or ResourceFiles) that are configured.

> NOTE: The EDKSession or entity search time is influenced by the EDKEngine settings (*e.g.* resource files (ECRs), entities enabled, other configuration settings), the size of the input file and the number of matches.

> NOTE: As of 25.4.0 `edktool` reads the entire file and submits that as text rather than using the EDK streaming input APIs. The edk_samples\eduction_from_config can be instrumented to measure processing speed that reflects use of the streaming input APIs.

### Running edktool benchmark

Run the following commands to see the output:

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples\eduction_from_config\resources
> edktool.exe benchmark -l ..\..\..\licensekey.dat -c test\config\test.cfg -i test\input\input.txt -s 3 -n 5
```

The key setting `-s 1` means one EDKSession (or thread) is run. The other key setting `-n 5` runs the same document 5 times in order to avoid any transient anomalies that may influence processing speed.  The individual iterations & threads are output along with an overall timing summary.

```txt
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


## Performance - Match Quality

`edktool` includes 2 processing modes to aid in quantifying match quality: measure and assess.  The use cases for these tools include:
- compare the extraction results from different versions of same grammar
- compare the extraction results for same grammar but with a different configuration
- monitor the accuracy of a grammar during development
- monitor the accuracy of a grammar as its improved over time

Refer to [Assess and Measure Named Entity Recognition Grammars](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/UseEduction/CompileTest/Eduction_Assess_Measure.htm) and [Results Relevance](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/UseEduction/ImproveMatches/ResultsRelevance.htm)for more information on this topic.

### Running edktool measure

`edktool measure` compares the XML output results from `edktool extract` yielding a report of match differences and the computation of precision / recall metrics.

In the [Custom Post Processing](./custom_postprocessing.md) lesson, an [Entity specific post-process score threshold](./custom_postprocessing.md#entity-specific-post-process-score-threshold) compares the output with and without the custom score threshold.  While tools like diff/windiff or Notepad++ Compare can illustrate the differences, `edktool measure` can yield more detailed results.  Let's see this in action.

> NOTE: The following assumes that you've completed the [Custom Post Processing](./custom_postprocessing.md) lesson.  However, the `expectations` folder contains the `edktool` output for the two test cases so you can proceed albeit with a lesser understanding of the test cases.

The expected results file was chosen to be `out_no_custom_pp_threshold.xml`, since it's the default behavior.  The actual results file is then the `out_custom_pp_threshold.xml`.  The use case is to compare the extraction results for the same grammar but with a different configuration.

```sh
> cd C:\OpenText\EductionGrammars_25.4.0_COMMON\pii\edk_samples\resources\custom_pp_threshold\expectations
> edktool measure -e out_no_custom_pp_threshold.xml -a out_custom_pp_threshold.xml -o out.EDK_MEASURE.xml

Eduction EDKTool Utility v25.4.0
Comparing the actual results in:
  out_custom_pp_threshold.xml
with the expected results in:
  out_no_custom_pp_threshold.xml
and sending the output to:
  out.EDK_MEASURE.XML

Precision=1, Recall=0.625

0.005 seconds elapsed
```

The `out.EDK_MEASURE.xml` file below contains the precision & recall summary metrics and also categorized match differences. 

```xml
<?xml version="1.0" encoding="UTF-8"?>
<XML>
  <EXPECTED_FILE>out_no_custom_pp_threshold.xml</EXPECTED_FILE>
  <ACTUAL_FILE>out_custom_pp_threshold.xml</ACTUAL_FILE>
  <EXPECTED_MATCHES_MISSING>
    <MATCHINFO DocId="Unknown" Entity="pii/id/nocontext/lu" Offset="32" N_Text="884228571" Score="0.4" />
    <MATCHINFO DocId="Unknown" Entity="pii/id/nocontext/lu" Offset="252" N_Text="AMS123456" Score="0.4" />
    <MATCHINFO DocId="Unknown" Entity="pii/id/nocontext/us" Offset="32" N_Text="884228571" Score="0.4" />
  </EXPECTED_MATCHES_MISSING>
  <ACTUAL_MATCHES_NOT_EXPECTED>
  </ACTUAL_MATCHES_NOT_EXPECTED>
  <DIFFERENT_MATCH_ATTRIBUTES>
  </DIFFERENT_MATCH_ATTRIBUTES>
  <PRECISION>1</PRECISION>
  <RECALL>0.625</RECALL>
</XML>
```

Since the `custom_pp_threshold.lua` script increased the score threshold from 0.4 to 0.45, the 3 `<EXPECTED_MATCHES_MISSING>` are expected.  Per the definition of [precision and recall](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/UseEduction/ImproveMatches/ResultsRelevance.htm), the computed precision & recall make sense. There are no false positives (FPs) in the actual file `out_no_custom_pp_threshold.xml` - 5 / (5 + 0) yielding a precision=1.0.  There are however 3 false negatives (FNs) as noted in `<EXPECTED_MATCHES_MISSING>` - 5 / (5 + 3) yielding a recall=0.625.

## Optimizing Performance

### Speed

Besides simplifying your configuration or getting a faster computer, there some settings that can impact performance.

For processing speed, here's some things to consider:

- use a pre-filter.  See [here](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/UseEduction/PreFiltering/PreFiltering.htm) for more details.
- set EntityMatchLimitN - See [here](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/Configuration/Eduction/_EDU_EntityMatchLimitN.htm) for more details.  In some applications, the existence of enough matches per each configured entity can be sufficient to take action based on the detected matches.
- For the PII, PHI, PCI grammars disable output normalization.  The name, address and date entities have output normalization enabled by default. See `scripts\names_stoplist.lua`, `scripts\address_stoplist.lua` and `scripts\normalize_date.lua` for details on how to configure.  Over enough matches (*e.g* tens vs thousands) the extra time to produce normalized output adds up.  Only some applications (*e.g.* searching on matches across a set of indexed documents) benefit normalized output.

## Conclusion

You now understand how to assess performance of Named Entity Recognition.

Next, why not try more tutorials to explore some of the other features available in Named Entity Recognition, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Named Entity Recognition SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/)
- [Knowledge Discovery Release Notes - Named Entity Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/SDKs/Eduction.htm)
