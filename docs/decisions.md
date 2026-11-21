# Decisions

The rulings of the project owner (Kevin) and the numbered decisions that apply them. They are the case law for one question that comes back all the time: *the game's code only matches with a form that looks odd: is that form original code, or is it steering the compiler?* Read this file before you write a single-use local, a `{}` block, a repeated store, a helper that only one function calls, a cast, or a retype, and before you drop one of them because "it only changes register allocation".

Source comments cite these texts: `ruling 2`, `P2`, `decision 48`, `decision 2026-11-14 #26` (which is decision 26 below). The numbering is stable: new decisions are added at the end and nothing is renumbered.

## Who decided

- **Kevin**: the nine rulings below, decision 9 (refusal), decisions 55, 56 and 57. They are marked *Kevin*.
- **Orchestrator, delegated**: on 2026-11-14 Kevin said: "take the recommended decisions from what I already answered; we want the code most faithful to the original". The principles P1 to P5 and decisions 1 to 8 and 10 to 54 (all but decision 9, which Kevin refused himself) were then taken by the maintainer's orchestrating agent from his rulings, case by case, as the questions came up in review. They are marked *delegated*. A delegated decision binds as long as Kevin does not overrule it; a question that no ruling, principle or decision covers goes to Kevin, not to the contributor who found it.
- A *reserved area* belongs to its contributor (Matheus): the `ui` namespace (see [CONTRIBUTING.md](../CONTRIBUTING.md)) and the other libraries he works on (`battle`, `eflib`, `grlib`, `anmlib`, `wnd` and the SDK declarations of `nn`). A function that needs a change there is left alone and reported to him; nobody edits those files for a match (principle P5).

## The rulings (Kevin)

The numbers are the order in which Kevin ruled; comments cite them as `ruling N`.

1. **Single-use local whose initialiser holds a call** (2026-11-13). Accepted when the local gives the game's real call order, shown by the assembly. Example: `seqWaitTalkEnd`. Code already on `main` that matches stays. A local that only reads a member (no call in its initialiser) is ruling 2.
2. **Single-use local that only reads a member** (2026-11-13). Accepted when the load it places is the game's, shown by the assembly: the game loads the member before another call or load, and the local is what puts the load there. Example: `initMpfMapParts`. Precedents on `main` stay.
3. **`{}` block around a variable without destructor, or a braced temporary** (`create({...})`) (2026-11-13). Accepted when the game's stack layout proves that the lifetime ends there (the slot is reused afterwards). Examples: `GfMenuObjBlDetail::create` (second cause), `GfMenuObjEvTheater::initialize`.
4. **A declaration or assignment order that only changes register allocation** (2026-11-13). Accepted when it is the only order that matches and the order itself is plausible code (`int y = 0; int x = 0;`, fields assigned in parameter order). Not accepted when it needs otherwise useless locals. Brought back: `shadowRender`, `createLookIK`. Still refused: the three `GfGameFlag` functions, whose bit-flag reader needs two single-use locals (`word`, `mask`) in `include/mm_mtl/bitflag.h` (see decision 9).
5. **A statement without effect that the game's code really holds** (2026-11-13): an extra `clear()` loop, a second release of a pointer already nulled, `if (x) ...; if (!x) ...` kept as two tests. Accepted when the assembly shows the operation. Brought back: `EffectLodManager::term`, `~GfMenuObjWorldMap`, `VoicePlayer::update`. The `DrLightObjGlobalIBL` constructor already on `main` stays.
6. **An argument the compiler erased** (2026-11-13). When the callee is defined in the same translation unit and never reads the parameter, clang drops the value and the register is never set. Keep the parameter (the mangled symbol proves it) and pass the most plausible expression, with a comment saying that the game never sets the register and that the original expression cannot be checked. Brought back: `DrMdoNomAfterImage::update` with `model->m_offsetPos`.
7. **A bit-table index the game computes unsigned (`lsr`) from a signed counter** (2026-11-13). Use one shared inline bit-test helper (inferred name `unknownNNN`, `u32` index, a comment with its role) instead of `static_cast<u32>(i) >> 5` at each call site. Applied to `readMpfModelCheck` (which also calls `DrMan::isGblIdx` instead of repeating it) and to the two functions on `main` that had the cast (`dr_mdo_ctl_seam_light.cpp`, `dr_mdo_ctl_seam_read.cpp`). If the helper does not match somewhere, report it before choosing another form.
8. **Code the original source genuinely duplicates** (2026-11-13). When another game function's statements are written again in a second function, and no call, unit grouping or flag reproduces the binary, write the statements out again, with a comment naming the function they repeat and the evidence (the instruction counts of the call form, measured by you). No macro. Brought back: `VoiceManager::playAuto` and `preloadAuto`, `GfMenuObjItemList2::ItemListListener::reciveEvent`; the six `IDColiGrandObj` callback blocks stay written out. The proof is the failed call form, not a preference: see [lessons](lessons.md), "Inlined helpers and duplicated source".
9. **An inline helper with a single user** (2026-11-14). A helper whose only proof is that its user matches with it and does not without it (clang optimises a separate function before inlining it; `LocatorReach::update` tests two members in one 32-bit load only through a helper) is accepted when no other valid form matches. The forms tried without it are listed in a comment, with the address. Kevin: such a helper gets a *descriptive* name marked `// Inferred name; ...` (as macros do), not `unknownNNN`; it is renamed if Torna or Xenoblade DE later shows a symbol. Covers `LocatorReach::update` (with its D0/D2, `getPos`, `getPosNum`), `StateFieldIdle::isEnableUnique`, `QuestID::unknown001`, `DevGraphQue`. AGENTS.md holds the exact marker comment.

## The principles (delegated, 2026-11-14)

Derived from rulings 1 to 9 and applied by the orchestrator to every question after them.

- **P1.** A member's or variable's type follows the game's own accesses, in any game function, matched or not. An existing type that nothing proves has no priority over the one the accesses show.
- **P2.** A single-use local is accepted when its position is visible in the game's instruction order: it places a call (ruling 1), a load (ruling 2) or a computation before another call, load or store, or it reproduces the game's block shape. It stays refused when its only effect is register allocation (Kevin's `GfGameFlag` `word`/`mask` refusal stands, decision 9).
- **P3.** A statement or store that the game's code holds is written, including redundant zero or non-zero stores visible in the assembly, and the same statement repeated where the same source pattern repeats (ruling 5).
- **P4.** Among forms that match, prefer the most natural code. The duplication of ruling 8 is allowed only when the call or helper provably does not match.
- **P5.** Reserved areas: ask the contributor who owns them, never edit.

## Index by topic

- Single-use locals, scopes, stores: 1, 2, 3, 10 to 14, 16, 17, 21, 33, 39, 44, 49.
- Member and variable types: 4, 6, 18, 19, 20, 35, 36, 48.
- Casts and byte offsets: 38, 40, 45, 47, 53, 54, 55.
- Helpers, names and written-out code: 25 to 32, 41, 42, 50.
- Devices kept out of the tree (declared but undefined specialisations, `inline` under the real name): 41, 51.
- Refusals: 9, 43, 46, 53.
- Questions for the owner of a reserved area: 22, 37, 52.

## The decisions

Each entry gives the question, the decision, its limits, and the evidence: a commit of `main`, or a game function and address. "Delegated" is the orchestrator's decision under Kevin's delegation (see above).

### 1. A `bool` carried out of a `{}` block

*Delegated.* A fade function declares `bool isChange` before a `{}` block (ruling 3) and reads it after the block. **Accepted**, as part of ruling 3: the flag is what the game keeps alive across the block, the slot of the block's own variable is what it reuses. Limit: only where the block itself is justified by the stack layout.

### 2. `GfMenuObjInn::DriverListener`: a store after `getPos` and a `u32` local

*Delegated.* `CtrlParam::unknown04 = 0` is written after the `getPos` call, and the listener keeps a `u32 driver` local. **Accepted**: the zero is part of the game's 64-bit store that comes after the call (P3), and the local places a call (ruling 1). Evidence: the store pair in `GfMenuObjInn::DriverListener::reciveEvent`.

### 3. `OpenParam()` constructor of the menu objects

*Delegated.* The `OpenParam()` constructor was incomplete compared with `GfMenuObjBladeSet::detailOpen`. **Decision**: the constructor zeroes both `unknown18` and `unknown1c`, as the game's `new OpenParam()` does. The `param.unknown1c = 0` that `GfMenuObjInn` had written becomes dead and is dropped if `GfMenuObjInn` still matches. `GfMenuObjBladeSet` comes back with `param.unknown18 = 0;` (P3: the game's `stp wzr, w8` shows it).

### 4. `DrPixlShadowObjDir::unknown338` as two floats

*Delegated.* The member was a `Pnt<f32>`, a mechanical guess; every reader loads a single float. **Accepted**: two `f32` members (P1).

### 5. `setInputDirPow` writes the matrix column by column

*Delegated.* Writing the three axes as the columns of the matrix is plausible code and the only order that matches. **Accepted** (ruling 4).

### 6. `FixedVectorUnit<16>` as `u16[8]`

*Delegated.* The question was whether the halfword unit could replace the current one so that `DevTouch::getPos`, `getMove` and `itDown` match. First answer: accepted, believing it matched a strict superset. **Corrected by measurement**: the halfword unit is not a superset (it breaks `fw::ColiCheckCallback::coli_callback`; a `float[4]` unit is the same and other units are worse). Nothing proves either unit, so **the current unit stays** and the three `DevTouch` functions stay blocked.

### 7. `setupTreeList`: a local copy of a table entry

*Delegated.* `mm::Vec3 inverse = unknown90[level];` in `idcoli::IDColiTreeTop::setupTreeList`. **Accepted**: a local copy of a table entry is natural code. A review of 2026-11-13 had removed this by-value copy because it only chooses the loop base pointer (the helper `ColiLinkList::unknown002` and an operand swap in `initCehckTree` had been written for it); this decision accepts the form again. The limit is P2: a copy of this kind must be natural code, not a register steer.

### 8. `getFieldSkillFromGimmik`: two variables

*Delegated.* The function keeps the raw `u16` and its widened `u32`. **Accepted**: the game holds both values (x22 and w21).

### 9. `GfGameFlag` bit-flag reader: the `word` and `mask` locals

*Kevin.* The reader in `include/mm_mtl/bitflag.h` matches only with two single-use locals (`word`, `mask`) whose only effect is register allocation. **Refused**, and it stays refused (the three `GfGameFlag` functions stay blocked). This is the standing example of the limit of P2.

### 10. `GfMenuGfObjAdapter::create`: `bool isUpdateAfter` before `operator new`

*Delegated.* **Accepted** (P2): the local places the flag before the allocation call.

### 11. `updateSepia` and `incSuppressEnemy`

*Delegated.* The three flags of `updateSepia` and the locals of `incSuppressEnemy` are **accepted** (rulings 1 and 2).

### 12. `execAbsSummon`: a local holding a call

*Delegated.* The local holds a call and its only effect is the shape of the blocks. **Accepted** (P2).

### 13. `createSearchObj`: a repeated store in the first block

*Delegated.* The first block repeats a store that the second block also has, and the assembly shows it in both. **Accepted** (P3: the same statement where the same pattern repeats).

### 14. `createMotionBlendObj`: `u32 offset`

*Delegated.* The local reproduces the block shape. **Accepted** (P2).

### 15. `#pragma pack` of the VM `unknown004`

*Delegated.* **Decision**: `pack(push, 1)`, because the game's loads exclude an alignment of 4; a comment records that an alignment of 2 also matches. `vmArgFunctionGet` and `vmOCNameGet` come back with it.

### 16. `vmThreadGetOC`: `package` and `function` locals

*Delegated.* **Accepted** (P2): they place the `add` before the `sbfiz`.

### 17. `DrPixlShadowRaytrace::debugRender`: `int y = halfHeight + 1;`

*Delegated.* **Accepted** (P2): the local places the `add` before the load.

### 18. `applyLinearVelocityAndRotY`: `unknownb0` as `f32`

*Delegated.* The member was `u32`. **Accepted** (P1): two game functions use it as a float.

### 19. FieldSkill: `u16 unknown5c` as two `bool`

*Delegated.* **Accepted** (P1): the game accesses the member by bytes in two functions.

### 20. A pair struct proven by one 64-bit store

*Delegated.* Applies to `EnvironmentInfo` and `Minimap2` (and `ArtsPalette` and `Compass`, already on `main`). **Accepted**: two adjacent members that the game stores as a unit with one 64-bit store, and does not merge with their neighbour, are evidence of a sub-object (a pair struct).

### 21. `int ctrl = startPresetCtrl(...)`

*Delegated.* The local fixes the order of two stores that come after the call. **Accepted** (P2).

### 22. `Queue::erase`, `size()` and `GfMenuObjExpGet::OpenParam() {}`

*Delegated, with a question for the owner of `anmlib`.* The seven `mm::mtl::Queue<T>::erase` instantiations of the `GfMenuObj...Info` classes (and `GfMenuObjExpGet::removeExpGet`) match with a fix of `include/mm_mtl/queue.h`, but three points needed a ruling.
(1) The `size() != 0` assert reads the size as 64 bits, so `size()` must return `size_t`; that breaks the one function that reads it as 32 bits, `anm::ThreadPool::threadFunc` in the reserved `anmlib`. **Decision**: ask the owner of `anmlib` for `anm::JobQueue::getJobCount()`, the accessor that Xenoblade DE keeps out of line (symbol `_ZNK3anm8JobQueue11getJobCountEv`, XC1DE 0x7100918220: `ldr w0, [x0, #0x10]; ret`), and call it in `threadFunc`. Until then the `erase` instantiations are not applied.
(2) After the shifting loop the game holds two `at()` asserts whose results it drops. The implementer picks the two semantically meaningful slots (the vacated end slot); ruling 5 covers that two calls exist, not which slots.
(3) `Queue<ExpGetInfo>::erase` copies 28 of the 32 bytes of the element, which needs `GfMenuObjExpGet::OpenParam() {}`, an empty constructor proven only by this instantiation. **Accepted** as a language rule, like `GmkDmgPhantom()` (decision 24); every user still matches. Applied.

### 23. `DevFileJobReadDvd::wkUpdate`: a bare `isSuspend();`

*Delegated.* A bare accessor call is not original code. **Decision**: write the test `if (DevFileTh::isSuspend()) { return; }`, which gives the same bytes.

### 24. `List::erase` and `GmkDmgPhantom()`

*Delegated.* **Kept** as they are on `main`.

### 25. `DevGraphQue::pushWholeRect` against the block form

*Delegated.* **Kept** as a helper, because `popRect` shows the same pattern (ruling 9).

### 26. The 20 event `setFlag` and `setDispFlag` helpers

*Delegated.* **Kept** with their descriptive names, plus the marker comment `// Inferred name`. AGENTS.md lists them as the one exception for multi-user helpers. Source comments cite this as `decision 2026-11-14 #26`.

### 27. `setCategoryMute` setter

*Delegated.* **Kept**: a setter on the category is plausible (the local form would also be accepted by P2).

### 28. `IDColiTreeTop::unknown036` bit helper

*Delegated.* **Kept**: ruling 7 extended to this bit helper.

### 29. `getClientScissorRect1`: the body inlined again

*Delegated.* **Kept**: ruling 8 plus ruling 2.

### 30. Declaration orders of ruling 4

*Delegated.* `DrAPCache::begin`, `InsertNext`, `calcDistSub` and `releaseTreeList` use orders that only change register allocation but read as plausible code. **Kept** (ruling 4).

### 31. The ten `fontLayerXxx` lookups

*Delegated.* They were written out ten times. **Decision**: one shared helper (`unknownNNN`, ten users). It matches, so the proof that ruling 8 requires (the call form does not match) is not made (P4).

### 32. `IDevFontInfo::unknown50()`

*Delegated.* A virtual function proven by a call at its vtable offset. **Accepted**.

### 33. `BgmManager::clear`: redundant `unknown63 = false`

*Delegated.* **Accepted** (P3) when the assembly shows the store. It does (`strb wzr, [sp, #107]` after the zeroing `stur xzr` of the `EventBgmSetup`, 0x71000aa2d0), but the function still did not match with it when decided (42 instructions against 42, only the scheduling of `cmp`/`adrp`/`fcsel` and of the byte stores 62/63 differs); `OnEventProc` was 59 against 60. The decision stands; the functions stay blocked until the scheduling is explained.

### 34. `found.unknown00 == m_end`

*Delegated.* The test of an iterator against the end in `ScnPoolObj::release` (twice), `updateMsg` and `setCurrent`. **Accepted**.

### 35. `DrPixlPostObjBloom`: six render targets

*Delegated.* **Decision**: retype the six bloom members to `DrPixlRenderTarget *` (P1: the constructor allocates that type), rework the release helper, bring `debugRender` and `calculateDownScaleImpl` back, and remove the cast in `bloomLensFlare`.

### 36. `unknown169`: a 16-byte struct in four detail menus

*Delegated.* **Accepted**: one sub-object cleared as a unit after the other members, in the same way in four classes.

### 37. `DevPadNx` and `EventData::unknown0c_f32`

*Delegated.* `include/nn/hid.h` (DevPadNx) and `EventData::unknown0c_f32` (MainMenu2BG) are in reserved areas. **Decision**: ask their owner (P5).

### 38. Reading a binary blob at byte offsets

*Delegated; extended 2026-11-15.* `plugin/bdat.cpp` reads the BDAT blob with byte-offset readers (`unknown005`, `unknown006`: `reinterpret_cast<u32 *>(bin + offset)`) and `pack(1)` on the sheet header. **Kept**: reading a binary blob at byte offsets is what the original parser does (the game adds the offset in bytes; a typed array would give a scaled address). `pack(1)` as decision 15. Extended to `dr/dr_env_coli_obj.cpp`, which already parsed the loaded environment-collision resource at byte offsets (`unknown006`, `007`, `008`, the `EnvColiPostData` lists) and now reads the cloud parameter records (`unknown011` to `unknown015`) of `updateCloudParams` the same way. Limit: `reinterpret_cast` stays refused elsewhere; decisions 47 and 54 extend the list.

### 39. `BgmEvent::isInvalidRequestBgmFile`: single-use `eventName`

*Delegated.* The local holds `c_str()`, whose address the game computes before the other operand's. **Kept** (P2): the instruction order is visible, not a register choice, and `c_str()` is a call in the source even when inlined.

### 40. `DrMdoGrpObj` constructor: one allocation carved into two arrays

*Delegated.* The constructor allocates one block and carves a list array and a pointer array from it with `static_cast<T **>(static_cast<void *>(unknown28 + count))`. **Kept**: the game really carves one block (0x71007cf6b0); a cast through `void *` within one allocation is the original's own code, not steering.

### 41. `CharaEvaPlayer::setSpMotWeapon` defined `inline` under its real name

*Delegated.* The game inlines exactly this body into `CharaEvaPlayer::update`; the standalone copy matches except one store order. **Kept**: the function is defined `inline` under its real name so that `update` inlines it, and the standalone copy stays a target (listed by `check`). A renamed helper would be less faithful. Limit: this is not a licence to hide a function that does not match with `inline`, `static`, an anonymous namespace or a renamed copy. Such a device needs its own decision (see decision 51); a function that does not match is removed from the tree instead.

### 42. `DrEnvColiParameter::updateCloudParams`: loops or written out

*Delegated.* Runs of up to 14 elements also match as loops; longer runs only match written out. **Decision**: write everything out. The long runs prove that the original wrote one statement per parameter, and a function that mixes loops and written-out runs is less plausible than one consistent style.

### 43. rcha `setup` name tables and hidden visibility

*Delegated.* The rcha `setup` name tables match only with `__attribute__((visibility("hidden")))` on each table. The library is not hidden as a whole: the `CRchaEx` constructor reads its vtable through the GOT (0x710069eb34). **Refused for now**: a per-symbol attribute only steers code generation and nothing shows that the original had one. The seven rcha functions stay blocked with that evidence.

### 44. `GfMenuObjHana::moveCharSubMenuIn`: `u32 move = 0;`

*Delegated.* The initialiser is dead (every path assigns the variable), yet the game's `mov w0, wzr` is hoisted above the branch only with it when compiled with `-g` (238 against 240 instructions; no difference without `-g`). **Kept**: a default-valued local is ordinary code, and the debug-info effect shows that the original had it. A separate variable holding the argument `0` would invent a name. Evidence: commit `cbb63953d`.

### 45. `ml::CacheDraw` primitive records

*Delegated.* `DRPNT`, `DRLINE`, `DRTRI`, `DRCUBE`, `DRARROW` and the others hold 12-byte vectors at 0xc, 0x18 and 0x24 (record sizes 0x18, 0x28... written by the `render*` constructors) and pass them by address, with no temporary, to functions whose mangled names take `const mm::Vec3 &` (`DRCUBE::flush` 0x71007065c0: `add x8,x0,#0xc; add x2,x0,#0x18; b renderCube`). **Accepted**: members of type `mm::Vec3NA` (the layout is proven) and, in the `flush` functions only, `reinterpret_cast<const mm::Vec3 &>(member)` at the binding, with this evidence in a comment: the original necessarily converted a 12-byte field to the reference of the 16-byte type (no cast-free typing gives both the stride and the mangled parameter). Limits: not a licence for other casts; the constructor copy form (64-bit plus 32-bit loads) is still open. Evidence: commit `8e052a399`.

### 46. A flat `f32[16]` view of `mm::Mat44`

*Delegated.* `DrPixlPostObjCubeMapIBL::getViewMatrixForFiltering` and the `CubeMapMultiIBL` one produce the game's 64-bit merged constant stores only through `f32 *m = &matrix.rows[0][0]; m[0..15]` (the natural `rows[r][c]` gives 74 instructions, the flat view 70). **Refused**: walking past the first row is out of bounds, and nothing in the game's symbols shows a flat accessor, union or 16-float constructor on `mm::Mat44` (no `_ZN2mm5Mat44` get, set, data or `operator[]` symbol); a layout change on a shared math type needs such evidence. Both functions stay blocked. Revisit if a sibling build shows a flat member. Evidence: commit `214ed626b`.

### 47. gmk `getBdatInfo()` accessors

*Delegated.* About twenty gmk headers on `main`, and one more in `GmkNpcIdInfo`/`GmkEnemyInsts`, have one-line `getBdatInfo()` accessors that read the bound BDAT record through `reinterpret_cast`. **Accepted** as an extension of decision 38: it is the same BDAT blob reading, at the gimmick's bound record. The accessor stays exactly the existing one-liner; no other cast is covered. Evidence: commit `e10c5b530`.

### 48. Flag words read with byte loads: `mm::mtl::unknown027<32>`

*Delegated.* A flag or state word that the game reads with byte loads, and that clang widens to `ldr x` plus `lsr` when the member is typed `u32` (a 4-byte member at an 8-aligned offset, next to a member read right after it). **Decision**: retype it to `mm::mtl::unknown027<32>`, the bit set of `include/mm_mtl/bitflag.h`, whose align-4 `this` keeps the narrow load; the enumerators become bit indices. Accepted when the siblings of the class use the same bit set at the same offsets (`BouManager` and `ManiManager` for `event::Manager`) or when the game's accesses are bit tests by index; the comment says which. Evidence: commit `e10c5b530` (`event::Manager::end`, `stop`, `fw::FootPlacementIKSolver::getRaycastUp`).

### 49. The named sender local of the message senders

*Delegated.* `GfObj *obj = static_cast<GfObj *>(...); component->recieveMessage(obj, message)`. In `WaterInPlugin::onEvent` the named local changes only the register allocation, but the same form is required in `GfComProperty::onDamage`, `onHeal` and `FootStepPlugin::emissionEffect` already on `main` (each fails without it in the same way). **Accepted** as a repeated source idiom of the message senders: one consistent form in four game functions is evidence of the original's writing, unlike a one-off register steer. Limit: do not extend it to unrelated single-use locals. Evidence: commit `2b143a2a4`.

### 50. New enumerators of an enum whose own name is invented

*Delegated.* The enum `unknown027` of the dr files has 22 enumerators `unknown027_N` on `main` (about 35 uses). **Decision**: new enumerators keep the existing `unknownNNN_N` form. Mixing two styles in one enum is worse, and the AGENTS.md `<PREFIX>_UNKNOWN_<N>` rule presupposes a prefix shared by named siblings, which such an enum does not have. A repository-wide normalisation, if wanted, is a separate cleanup commit. Evidence: commit `53aada686`.

### 51. A declared, undefined specialisation of `gmk::isGmkValidViewUnbound<T>`

*Delegated.* One template body matches the `GmkEnemy`, `GmkMob` and `GmkRoutedMob` instances, but defining the template also emits the `GmkRoutedEnemy` instance (0x71005e0d5c), which does not match. **Accepted as a temporary, commented device**: `template <> bool isGmkValidViewUnbound<GmkRoutedEnemy>(const AGmkBase &);` is declared without a definition. The unmatched instance stays a target listed by `check` (nothing is hidden), the three matched instances share the single original body, and the declaration must be removed as soon as the `GmkRoutedEnemy` instance matches. Limit: not a licence for other templates, unless one shared body matches and the excluded instance stays listed. Evidence: commit `3c1d94104`.

### 52. The `s64 / 1000` of the movie and ssd code

*Delegated; raised by Matheus in issue #4 (2026-11-20).* The movie and ssd code divides an `s64` by `1000` or `1000000`, which the game computes with a split 32-bit reciprocal multiply instead of `smulh`, always on the result of `nn::os::ConvertToTimeSpan` (11 XC2 sites; the same in Torna and XC1DE; about 44 sites in XC1DE's SDK module; a plain `/1000` gives `smulh` there too). **Decision**: members of `nn::TimeSpan` (`unknown001` microseconds, `unknown002` milliseconds, a shared multiply `unknown003` if it matches for both), because nnheaders has no getters, so no SDK name may be used (AGENTS.md). The comment gives the role, the forms tried and the addresses. Only matching users go in; no general divide helper elsewhere. `include/nn` is Matheus's area, so he writes it.

### 53. `FixedObjectAllocator<FileHandleTh, 640>::allocate`

*Delegated.* The function is byte-identical only with the object addressed as a byte index into the storage (`reinterpret_cast<T *>(unknown00 + i * sizeof(T))`) and the loop bound read through a raw byte offset of `this` (`*reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(this) + ...)`). The cause is the loop strength reduction register choice of clang 3.9. **Refused**: raw byte offsets of `this` are forbidden (CONTRIBUTING.md), and the form is chosen for the register allocation, not shown by an access. The byte-index storage access alone (112 instructions against 107) does not match either, so nothing lands. Reopen only with a natural form or a body seen in a sibling build.

### 54. Resource-blob casts in the dr resource parsers

*Delegated.* `reinterpret_cast<const T *>(data + offset)` on model and resource blobs in `DrResMdoSeamWrkPosMpf::setupInstMpf` (three `unknown08` assignments), outside the two files that decision 38 names. The same form is already on `main` in `DrResMdoSeamWrkMpf::changeMemCall`, `DrResMdoSeamWrkPosInst::changeMemEtcInstPos` and `DrMdoCtlMpfAuto::changeMemAutoMpf`. **Accepted**, extending decision 38 to the dr resource blob parsers: the symbols fix a `const u8 *` blob parameter and typed callees, so the original adds byte offsets to the blob and casts; no cast-free form exists. Limit: only a resource blob plus a header offset read from that blob; `reinterpret_cast` stays refused everywhere else (no casts of `this`, no punning of game objects).

### 55. The FixStr reverse search

*Kevin, 2026-11-20.* The inlined `FixStr` reverse search (about 33 game functions: `PathUtil`, `GfMenuMapInfo`, `ui::UIUtil::make*FileName`, `normalizeFileName`, `makeFullPath`...) keeps `mData - 1` hoisted. Only a base computed through an integer round trip (`reinterpret_cast<const char *>(reinterpret_cast<size_t>(c_str()) - 1)`) reproduces it (loop strength reduction; about 600 natural forms were tried). With `c_str()` and `length()` accessors and a `do { } while (--i != 0)` loop behind `length() != 0`, one helper matches 17 functions byte for byte across four libraries and the search loops of nine more, with no contradicting case. **Accepted** as a documented exception confined to this one `FixStr` helper (`unknownNNN`, with a comment holding the evidence and the forms tried). It is not a precedent: integer round trips stay refused everywhere else (decision 53 stands). The nine `ui::UIUtil` users belong to the owner of `ui`. Evidence: commit `1576fa595`.

### 56. Assert-free container templates for `skt`

*Kevin, 2026-11-21.* `skt::CommandManager::create`, `recvBinary`, `recvCommand`, `updateCallback`, `removePort` and `PortInfo::destroy` use the `mm::mtl` container templates without the asserts that every other copy in the game has (the skt library was built against an older container version). **Accepted**: an assert-free copy of the needed container templates, local to `skt` (its own header under the skt area, used only by skt), with a comment citing the missing asserts in those game functions (addresses) as evidence. Not shared with any other area: `include/mm_mtl` stays the single implementation elsewhere.

### 57. The party-map save helper (0x71003558e8) and its callers

*Kevin, 2026-11-21.* The party-map save helper at 0x71003558e8 (and with it `GfGameUtilSaveData::setupGameSaveData`, 476 instructions, and `getSaveData(SDataGame &)`) matches only with single-use locals, `f32 driverDeg = rot * mm::RAD_TO_DEG; f32 bladeDeg = ...;`. At first sight they only change register allocation, which P2 refuses (decision 9). **Accepted** (Kevin: "if there is only one solution and we are sure there is no other, go"), after an exhaustive search: 83 hand-written forms, two permuter runs (1311 candidates, 158 matching sources, all with a variable bound to the product) and about 170 more forms elsewhere. The mechanism was found: the IR and the register allocation are identical with and without the locals. Only `AArch64A57FPLoadBalancing` differs, because under `-g` a named variable leaves a `DBG_VALUE` between the `fmul` and its store, so the chain keeps `s0` (the game has s0, s0, s1, s1, s0, s1). This is the same kind of evidence as decision 44 (a variable visible under `-g`), so P2 does not apply. Both locals are kept, the symmetrical form (the game cannot tell it from a blade-only one). The evidence is in a comment at the helper. Limit: this accepts these locals on that evidence; it does not make register-allocation-only locals acceptable in general. Commit: pending.

### Everything else

Paragraphs of the first review that rulings 1 to 9 already answered (`seqWaitTalkEnd`, `loadStart`, `GfComBehaviorMob`, `initMpfMapParts`, `readMpfModelCheck`, `playAuto`, `VoicePlayer`, `EffectLodManager`, `WorldMap` destructor and `getFloor`, `HanaParts`, `setupAddBooster`, `LinkJump`, three `initialize`, `EvTheater`, `ProcException::wkRender`, `createLookIK`, `shadowRender`, `DrMdoNomAfterImage`, `ItemList2`, `MissionList`, `gevChangeScenarioFlag`, `LvUp`, `Launch`...) are decided: restore any that is not on `main` yet.

## Questions waiting for the owner of a reserved area

Open requests to Matheus that no decision above resolves. None blocks a match outside his areas.

- `anm::JobQueue::getJobCount()` (decision 22).
- `DevPadNx` in `include/nn/hid.h` and `EventData::unknown0c_f32` (decision 37).
- `nn::TimeSpan` members for the reciprocal-multiply divisions (decision 52).
- `ui::UIUtil::make*FileName`: nine functions that match with the helper of decision 55 and wait for the owner of `ui`.
- `wnd::GlobalWind::update`: `WindWorld::updateGlobalWind` (0x710098a710) repeats `GlobalWind::update` (0x7100988d40). Defining `update` in the class body of `wnd_wind.h` (the game emits it with the vtable, with no direct call) and calling it makes both match (26 and 29 instructions).
- `ui::EventData()` zeroing order: the game zeroes the members in descending order (`unknown14`, `unknown10`, `unknown0c`, `unknown08`, `unknown00`); `GfMenuObjDropItem::open` matches fully with a constructor that assigns in that order.
- `eflib` `SendParam` constructor: the game's inlined constructor stores `unknowna3 = 1` after `unknowna2 = 0` (seen in `GmkJump`, `GmkCollection` and `GmkWarp` `validateIconPos`, 0x7100613680, 0x7100608108, 0x71006148a0). Moving the assignment in `include/eflib/effect_send_param.h` fixes that part of those functions.
- `ui::UIListInfoBase::getSize` signedness: the game compares the event index with the list size as signed integers (`GfMenuObjMercenaryForm::UnitListener::reciveEvent`, `cmp w20, w0; b.ge` at 0x7100492a54 and 0x7100492aec), while the reserved header declares `u32`. The matching form casts it, and the same cast is already used in `GfMenuCharDataAdapter`, `GfMenuArtsAdapter`, `GfMenuFieldSkillAdapter::ListConverter::getFieldSkill`, `GfMenuObjBladeCreate`, `GfMenuObjCommonJog`, `GfMenuObjInn` and `GfMenuObjOption`. By P1 the likely cause is the return type of `getSize`; the question is whether it is `int`.
- A `void *` or typed view of `EventData`'s 0x08 slot would remove the `reinterpret_cast` of `event.unknown08_u64` in `GfMenuObjBalloon::SelMoneyListener::reciveEvent` (commit `7106fde12`) and `GfMenuObjQuestReward::RewardListener::reciveEvent`. Low priority.
