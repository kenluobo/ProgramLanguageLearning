; ModuleID = 'cf.cpp'
source_filename = "cf.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main(i32 noundef %0, ptr noundef %1) #0 !dbg !10 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
    #dbg_declare(ptr %4, !18, !DIExpression(), !19)
  store ptr %1, ptr %5, align 8
    #dbg_declare(ptr %5, !20, !DIExpression(), !21)
    #dbg_declare(ptr %6, !22, !DIExpression(), !23)
  %7 = load i32, ptr %4, align 4, !dbg !24
  %8 = icmp sgt i32 %7, 2, !dbg !26
  br i1 %8, label %9, label %11, !dbg !26

9:                                                ; preds = %2
  %10 = load i32, ptr %4, align 4, !dbg !27
  store i32 %10, ptr %6, align 4, !dbg !29
  br label %12, !dbg !30

11:                                               ; preds = %2
  store i32 -1, ptr %6, align 4, !dbg !31
  br label %12

12:                                               ; preds = %11, %9
  %13 = load i32, ptr %6, align 4, !dbg !33
  %14 = add nsw i32 %13, 42, !dbg !33
  store i32 %14, ptr %6, align 4, !dbg !33
  %15 = load i32, ptr %6, align 4, !dbg !34
  ret i32 %15, !dbg !35
}

attributes #0 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.linker.options = !{}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "cf.cpp", directory: "/home/klb/Code/ProgramLanguageLearning/cplusplus/llvm-ir/controlFlow", checksumkind: CSK_MD5, checksum: "4ed381231503d422389d0a8a0280ffb0")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)"}
!10 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !11, scopeLine: 2, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !17)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !13, !14}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64)
!16 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!17 = !{}
!18 = !DILocalVariable(name: "argc", arg: 1, scope: !10, file: !1, line: 1, type: !13)
!19 = !DILocation(line: 1, column: 14, scope: !10)
!20 = !DILocalVariable(name: "argv", arg: 2, scope: !10, file: !1, line: 1, type: !14)
!21 = !DILocation(line: 1, column: 26, scope: !10)
!22 = !DILocalVariable(name: "x", scope: !10, file: !1, line: 3, type: !13)
!23 = !DILocation(line: 3, column: 9, scope: !10)
!24 = !DILocation(line: 4, column: 9, scope: !25)
!25 = distinct !DILexicalBlock(scope: !10, file: !1, line: 4, column: 9)
!26 = !DILocation(line: 4, column: 14, scope: !25)
!27 = !DILocation(line: 5, column: 13, scope: !28)
!28 = distinct !DILexicalBlock(scope: !25, file: !1, line: 4, column: 19)
!29 = !DILocation(line: 5, column: 11, scope: !28)
!30 = !DILocation(line: 6, column: 5, scope: !28)
!31 = !DILocation(line: 7, column: 11, scope: !32)
!32 = distinct !DILexicalBlock(scope: !25, file: !1, line: 6, column: 12)
!33 = !DILocation(line: 10, column: 7, scope: !10)
!34 = !DILocation(line: 12, column: 12, scope: !10)
!35 = !DILocation(line: 12, column: 5, scope: !10)
