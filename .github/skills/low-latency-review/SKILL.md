---
name: low-latency-review
description: "Review MiniTrader implementations for low-latency trading correctness and performance. Use when reviewing code for memory ordering, lock-free structures, race conditions, order books, networking latency, benchmark quality, or fixed-income modeling."
argument-hint: "Files, symbols, or changes to review"
user-invocable: true
---

# Low-Latency Review

## When To Use

- Review a user implementation after a learning step is complete.
- Audit multithreaded code, lock-free structures, event loops, or benchmarking code.
- Check whether a design change adds latency, contention, or modeling risk.

## Review Procedure

1. Anchor the review on the concrete file, symbol, diff, failing test, or runtime behavior.
2. Read only enough surrounding code to understand the controlling path, invariants, and hot-path costs.
3. Report findings first, ordered by severity.
4. For each finding, explain why it is risky for correctness or latency and cite the local evidence in the code.
5. Cover the relevant categories below.
6. End with one focused next experiment, test, or benchmark that would validate the current design.

## Review Categories

- Concurrency correctness: happens-before edges, atomic ordering, shutdown sequencing, ABA risk, lifetime bugs, torn reads.
- Hot-path cost: heap allocation, copies, branchiness, cache-line contention, false sharing, syscalls, avoidable indirection.
- Data layout and ownership: padding, alignment, ownership transfer, timestamp semantics, strong domain aliases instead of raw primitives.
- Networking path: batching, backpressure, buffer ownership, serialization overhead, kernel crossings, timestamp placement.
- Benchmark quality: warmup, pinning, clock source, realistic traffic shape, percentile reporting, measurement distortion.
- Fixed-income modeling: instrument assumptions, tick or yield representation, precision, and settlement or market-structure constraints.

## Review Rules

- Do not fully rewrite the core algorithm unless the user explicitly asks for implementation help.
- Prefer patch-level suggestions, invariants, and targeted pseudocode over full replacements.
- Do not accept `memory_order_relaxed` or `seq_cst` without a concrete justification.
- If product type affects correctness and is unclear, ask whether the scope is cash bonds, repo, swaps, or another instrument.
- If no serious findings exist, say that explicitly and then list residual risks or missing measurements.
- If measurement infrastructure is missing, recommend the smallest benchmark or test harness needed before optimization.