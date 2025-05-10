; ModuleID = 'cfWhile.cpp'
source_filename = "cfWhile.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z3addii(i32 noundef %0, i32 noundef %1) #0 !dbg !10 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
    #dbg_declare(ptr %3, !15, !DIExpression(), !16)
  store i32 %1, ptr %4, align 4
    #dbg_declare(ptr %4, !17, !DIExpression(), !18)
  %5 = load i32, ptr %3, align 4, !dbg !19
  %6 = load i32, ptr %4, align 4, !dbg !20
  %7 = add nsw i32 %5, %6, !dbg !21
  ret i32 %7, !dbg !22
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main(i32 noundef %0, ptr noundef %1) #1 !dbg !23 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
    #dbg_declare(ptr %4, !29, !DIExpression(), !30)
  store ptr %1, ptr %5, align 8
    #dbg_declare(ptr %5, !31, !DIExpression(), !32)
    #dbg_declare(ptr %6, !33, !DIExpression(), !34)
  br label %7, !dbg !35

7:                                                ; preds = %25, %2
  %8 = load i32, ptr %4, align 4, !dbg !36
  %9 = add nsw i32 %8, -1, !dbg !36
  store i32 %9, ptr %4, align 4, !dbg !36
  %10 = icmp sgt i32 %8, 0, !dbg !37
  br i1 %10, label %11, label %26, !dbg !35

11:                                               ; preds = %7
  %12 = load i32, ptr %4, align 4, !dbg !38
  %13 = srem i32 %12, 2, !dbg !41
  %14 = icmp eq i32 %13, 0, !dbg !42
  br i1 %14, label %15, label %20, !dbg !42

15:                                               ; preds = %11
  %16 = load i32, ptr %6, align 4, !dbg !43
  %17 = load i32, ptr %6, align 4, !dbg !45
  %18 = sub nsw i32 %17, 1, !dbg !46
  %19 = call noundef i32 @_Z3addii(i32 noundef %16, i32 noundef %18), !dbg !47
  store i32 %19, ptr %6, align 4, !dbg !48
  br label %25, !dbg !49

20:                                               ; preds = %11
  %21 = load i32, ptr %6, align 4, !dbg !50
  %22 = load i32, ptr %6, align 4, !dbg !52
  %23 = add nsw i32 %22, 1, !dbg !53
  %24 = call noundef i32 @_Z3addii(i32 noundef %21, i32 noundef %23), !dbg !54
  store i32 %24, ptr %6, align 4, !dbg !55
  br label %25

25:                                               ; preds = %20, %15
  br label %7, !dbg !35, !llvm.loop !56

26:                                               ; preds = %7
  %27 = load i32, ptr %6, align 4, !dbg !59
  ret i32 %27, !dbg !60
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.linker.options = !{}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "cfWhile.cpp", directory: "/home/klb/Code/ProgramLanguageLearning/cplusplus/llvm-ir/controlFlow/whileStat", checksumkind: CSK_MD5, checksum: "0f040e915c703e01a88c371f39514a24")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 8, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 2}
!8 = !{i32 7, !"frame-pointer", i32 2}
!9 = !{!"clang version 20.1.1 (https://github.com/llvm/llvm-project.git 424c2d9b7e4de40d0804dd374721e6411c27d1d1)"}
!10 = distinct !DISubprogram(name: "add", linkageName: "_Z3addii", scope: !1, file: !1, line: 1, type: !11, scopeLine: 1, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !13, !13}
!13 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!14 = !{}
!15 = !DILocalVariable(name: "left", arg: 1, scope: !10, file: !1, line: 1, type: !13)
!16 = !DILocation(line: 1, column: 13, scope: !10)
!17 = !DILocalVariable(name: "right", arg: 2, scope: !10, file: !1, line: 1, type: !13)
!18 = !DILocation(line: 1, column: 23, scope: !10)
!19 = !DILocation(line: 2, column: 10, scope: !10)
!20 = !DILocation(line: 2, column: 17, scope: !10)
!21 = !DILocation(line: 2, column: 15, scope: !10)
!22 = !DILocation(line: 2, column: 3, scope: !10)
!23 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 5, type: !24, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !14)
!24 = !DISubroutineType(types: !25)
!25 = !{!13, !13, !26}
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64)
!28 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!29 = !DILocalVariable(name: "argc", arg: 1, scope: !23, file: !1, line: 5, type: !13)
!30 = !DILocation(line: 5, column: 14, scope: !23)
!31 = !DILocalVariable(name: "argv", arg: 2, scope: !23, file: !1, line: 5, type: !26)
!32 = !DILocation(line: 5, column: 26, scope: !23)
!33 = !DILocalVariable(name: "x", scope: !23, file: !1, line: 6, type: !13)
!34 = !DILocation(line: 6, column: 7, scope: !23)
!35 = !DILocation(line: 7, column: 3, scope: !23)
!36 = !DILocation(line: 7, column: 13, scope: !23)
!37 = !DILocation(line: 7, column: 16, scope: !23)
!38 = !DILocation(line: 8, column: 8, scope: !39)
!39 = distinct !DILexicalBlock(scope: !40, file: !1, line: 8, column: 8)
!40 = distinct !DILexicalBlock(scope: !23, file: !1, line: 7, column: 20)
!41 = !DILocation(line: 8, column: 13, scope: !39)
!42 = !DILocation(line: 8, column: 17, scope: !39)
!43 = !DILocation(line: 9, column: 15, scope: !44)
!44 = distinct !DILexicalBlock(scope: !39, file: !1, line: 8, column: 22)
!45 = !DILocation(line: 9, column: 18, scope: !44)
!46 = !DILocation(line: 9, column: 19, scope: !44)
!47 = !DILocation(line: 9, column: 11, scope: !44)
!48 = !DILocation(line: 9, column: 9, scope: !44)
!49 = !DILocation(line: 10, column: 5, scope: !44)
!50 = !DILocation(line: 11, column: 15, scope: !51)
!51 = distinct !DILexicalBlock(scope: !39, file: !1, line: 10, column: 12)
!52 = !DILocation(line: 11, column: 18, scope: !51)
!53 = !DILocation(line: 11, column: 19, scope: !51)
!54 = !DILocation(line: 11, column: 11, scope: !51)
!55 = !DILocation(line: 11, column: 9, scope: !51)
!56 = distinct !{!56, !35, !57, !58}
!57 = !DILocation(line: 13, column: 3, scope: !23)
!58 = !{!"llvm.loop.mustprogress"}
!59 = !DILocation(line: 15, column: 10, scope: !23)
!60 = !DILocation(line: 15, column: 3, scope: !23)
