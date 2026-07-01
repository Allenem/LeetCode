# Agent 智能体知识点

## 一个完整的 Agent 智能体架构一般包括哪些部分？

学术界和工业界对 Agent 架构有高度一致的共识，核心组件包括：

（1）Profile / 角色定义
- System Prompt 定义 Agent 的身份、能力边界、行为约束
- 例如："你是一个高级数据分析师，擅长 SQL 查询和数据可视化"

（2）Planning / 规划模块
- 任务分解（Task Decomposition）：将复杂目标拆解为可执行的子任务
- 策略选择：决定执行顺序和方法
- 典型范式：CoT（Chain-of-Thought）、ReAct、Plan-and-Solve、Tree-of-Thought

（3）Memory / 记忆系统
- 短期记忆（Short-term Memory）：当前对话的上下文窗口
- 长期记忆（Long-term Memory）：通过向量数据库、KV 存储等持久化历史信息
- 工作记忆（Working Memory）：Agent 当前推理链中的中间状态

（4）Tools / 工具集
- 搜索引擎、代码解释器、API 调用、数据库查询、文件操作等
- 通过 Function Calling / Tool Use 协议与 LLM 集成
- MCP（Model Context Protocol）是 2025 年兴起的工具标准化协议

（5）Action / 行动执行器
- 将 LLM 的决策转化为实际操作
- 包括工具调用的执行、结果的收集和格式化

（6）Observation / 感知与反馈
- 收集行动执行的结果
- 将外部环境的反馈注入到下一轮推理中

（7）Orchestration / 编排层
- Agent Loop 的核心控制逻辑
- 状态管理、错误处理、退出条件判断、超时控制

这七个组件共同构成了一个完整的 Agent 系统。在工程实践中，还需要加上可观测性（Observability）层用于监控和调试、安全护栏（Guardrails）层用于防止异常行为。

## Agent 的工作模式都有什么？

这是对 Agent 推理-执行范式的考察，主流工作模式包括：

（1）ToolsCallingAgent（工具调用型）
- 最基础的模式，LLM 根据用户请求直接选择并调用工具
- 流程：用户输入 → LLM 决定调用哪个工具 → 执行工具 → 返回结果
- 适用场景：简单的单步任务，如天气查询、翻译
- 代表实现：OpenAI Function Calling

（2）ReActAgent（推理-行动型）
- 来自 Yao et al., 2022 论文，核心是 Thought → Action → Observation 的循环
- LLM 先"思考"（生成推理链），再"行动"（调用工具），然后"观察"（分析结果），循环直至得出最终答案
- 优点：可解释性强，可追踪推理过程，自我纠错能力较好
- 缺点：每轮推理需要额外的模型调用，延迟和成本较高；错误可能在循环中传播
- 适用场景：复杂的多步推理任务，需要动态适应的场景

（3）ReflectionAgent（反思型）
- 在 ReAct 基础上增加了自我评估层
- Agent 生成初始响应后，切换到"批评者"模式，检查准确性、逻辑一致性
- 如果发现问题，自动修正并重新生成
- 典型实现：Reflexion 框架
- 适用场景：对准确性要求极高的场景，如代码生成、学术写作

（4）PlanAndSolveAgent（规划-执行型）
- 先制定全局计划，再逐步执行
- 流程：用户输入 → Planner 生成步骤列表 → Executor 依次执行每个步骤 → 汇总结果
- 优点：对复杂任务有更好的全局视野，不容易陷入局部循环
- 缺点：计划一旦确定，灵活性不足；重新规划成本高
- 适用场景：步骤明确的多步任务，如数据分析、报告生成

（5）Multi-Agent（多智能体协作型）
- 多个专业化 Agent 协作完成复杂任务
- 模式包括：层级式（一个 Orchestrator + 多个 Worker）、对话式（Agent 之间互相交流）、竞争式（多个方案择优）
- 代表框架：CrewAI、AutoGen、MetaGPT
- 适用场景：软件开发（PM → 架构师 → 开发 → 测试）、复杂研究

（6）Human-in-the-Loop（人机协作型）
- 在关键节点暂停执行，等待人类审核、批准或提供输入
- 适用场景：高风险决策（金融交易、法律文书）、需要人类判断的创意任务

选择建议：从简单模式开始，按需增加复杂度。单 Agent + ReAct 能解决大部分真实场景，不要过早引入多 Agent。

## 了解过 Agent 的设计范式吗？了解其他的 Agent 范式吗？

Agent 设计范式是更高层次的架构方法论，目前业界公认的七大设计范式：

① ReAct 范式（推理+行动）
- 交替进行推理和行动，是最基础也最重要的单 Agent 模式
- 推荐作为复杂任务的默认起点

② Reflection 范式（自我反思）
- Agent 输出后进行自我评估，发现错误后迭代改进
- 实现方式：Critic Agent 审查 Actor Agent 的输出

③ Tool Use 范式（工具使用）
- Agent 作为工具编排器，智能选择和组合外部工具
- 关键挑战：工具描述的清晰度直接影响 Agent 的工具选择准确性

④ Planning 范式（规划先行）
- 先生成执行计划，再按计划执行
- 变体：Plan-and-Solve、LATS（Language Agent Tree Search）、AdaPlanner（自适应规划）

⑤ Multi-Agent Collaboration 范式（多智能体协作）
- 多个专业化 Agent 分工合作
- 子模式：Sequential（串行管道）、Parallel（并行执行）、Hierarchical（层级调度）

⑥ Sequential Workflow 范式（流水线工作流）
- 预定义的步骤序列，每步处理结果传递给下一步
- 确定性强，适合业务流程固定的场景

⑦ Human-in-the-Loop 范式（人机协同）
- 人类作为 Agent 系统的一部分参与决策
- 适合高风险、需要合规审核的场景

其他前沿范式：

- LATS（Language Agent Tree Search）：结合蒙特卡洛树搜索进行探索式规划
- Voyager：在 Minecraft 中实现自主探索和技能积累的终身学习 Agent
- Generative Agents：斯坦福小镇，模拟人类社会行为的 Agent 架构
- Self-Discover：让 LLM 自主发现并组合推理策略
- RAISE：结合了记忆检索和反思的综合框架

## 了解过市面上有哪些智能体 Agent 吗？

可以从框架层和产品层两个维度回答：

开发框架层：

- LangChain / LangGraph：最广泛采用的 Agent 框架，LangGraph 提供图状态编排，支持复杂的有状态工作流
- CrewAI：基于角色的多 Agent 协作框架，超过 10 万开发者通过社区课程获得认证
- AutoGen / Microsoft Agent Framework：微软将 AutoGen 和 Semantic Kernel 合并为统一的 Agent Framework，1.0 GA 版本目标 2026 Q1 发布
- LlamaIndex：专注于 RAG 和知识密集型 Agent 工作流
- SmolAgents（HuggingFace）：轻量级 Agent 框架，核心逻辑约 1000 行代码
- MetaGPT：模拟软件开发团队的多 Agent 系统
- Dify / Coze：低代码 Agent 搭建平台

产品层：

- Claude Code：Anthropic 的命令行 Agent 编码工具
- ChatGPT with Plugins / GPTs：OpenAI 的消费级 Agent
- GitHub Copilot：代码 Agent，超 80% BNY Mellon 开发者日常使用
- Cursor / Windsurf：AI 编码 IDE，集成 Agent 式交互
- Devin：Cognition 的自主软件工程 Agent
- Manus：2025 年爆火的通用 Agent 产品
- Perplexity：搜索型 Agent
- AutoGPT / AgentGPT：早期的自主 Agent 先驱

## Agent Loop

```
while not done:
    1. 感知（Perceive）：获取当前状态、用户输入、环境反馈
    2. 思考（Think）：LLM 推理，决定下一步行动
    3. 行动（Act）：执行工具调用、生成内容等
    4. 观察（Observe）：收集行动结果
    5. 判断（Evaluate）：任务是否完成？是否需要继续？
```

## 你认为当前 Agent 技术难以突破的核心瓶颈有哪些？

这是一道考察技术深度和行业洞察的开放题，需要从多个层面回答：

① 可靠性瓶颈（Reliability）
- Agent 的错误会级联传播：ReAct 循环中某一步的错误会影响后续所有步骤
- LLM 的幻觉问题在 Agent 场景中被放大：幻觉可能导致错误的工具调用，产生不可预知的后果
- 行业数据：LangChain 调研中 32% 的受访者将"质量"列为 Agent 投产的最大障碍

② 规划能力不足（Planning）
- 当前 LLM 的规划能力仍然有限，面对复杂任务容易制定次优甚至错误的计划
- 长链任务中容易"迷失"，忘记最初目标
- 自我纠错能力有限，经常在错误方向上"执着"

③ 成本与延迟（Cost & Latency）
- Agent 的多轮交互导致 Token 消耗量远超单次调用，成本非线性增长
- 每增加一个推理步骤就增加一次 LLM 调用，延迟累积
- 编码 Agent 单次会话可能涉及 50-100 次 API 调用

④ 长上下文退化（Context Rot）
- 即使模型支持百万级 Token 窗口，实际性能随上下文增长显著下降
- "Lost in the Middle" 现象：模型对上下文中间位置的信息召回率明显低于首尾
- Chroma 的研究表明，大多数模型在达到标称上下文长度之前就开始不可靠

⑤ 安全与可控性（Safety & Control）
- Agent 具有执行外部操作的能力（删除文件、发送请求等），风险远高于纯文本生成
- Prompt Injection 攻击在 Agent 场景更危险
- 缺乏成熟的权限控制和审计机制

⑥ 评测标准缺失（Evaluation）
- 缺乏统一的 Agent 能力评测基准
- 传统的 NLP 评测指标不适用于 Agent 的动态交互场景
- LangChain 调研显示只有 52% 的组织实施了 Agent 评测

⑦ 可观测性不足（Observability）
- Agent 的多步执行过程难以追踪和调试
- 故障定位困难：不清楚是 LLM 推理错误还是工具返回错误还是上下文污染
- 好消息是 89% 的组织已实施某种形式的 Agent 可观测性

## Workflow 和 Agent 有什么区别？

核心区别一句话：Workflow 是"你告诉系统怎么做"，Agent 是"你告诉系统做什么，它自己决定怎么做"。

Anthropic 官方的划分标准：

- Workflow = Orchestration framework + Predefined paths（预定义路径）
- Agent = LLM dynamically directs its own processes and tool usage（LLM 自主控制）

## 什么情况下适合用 Workflow，什么情况下适合用 Agent？

适合 Workflow 的场景：

- 业务流程固定且明确，如"客户投诉处理 → 分类 → 分配 → 响应"
- 对可靠性和一致性要求极高（金融、医疗合规场景）
- 需要精确的成本控制和 SLA 保证
- 团队对 AI 能力边界有清晰认知，可以预定义最优路径
- 每个节点的输入输出格式确定
- 需要严格的审计追踪

适合 Agent 的场景：

- 任务需求多样且难以穷举所有路径
- 需要根据中间结果动态调整策略
- 用户的请求本身就是开放式的（如"帮我调研 XX 行业"）
- 需要探索性地使用多种工具
- 对延迟和成本容忍度较高

混合模式（实际项目中最常见）：
- 顶层用 Workflow 做整体编排，保证核心流程可控
- 某些节点内部使用 Agent 处理需要灵活推理的子任务
- 例如：客服系统整体是 Workflow（意图识别→路由→处理→回复），但"处理"节点内部用 Agent 来灵活地查询知识库和生成回答

## 如何保证 Workflow 和 Agent 的成功率？

Workflow 成功率保障：

1. 节点级保障：每个节点配备输入校验、输出校验和 fallback 逻辑
2. Prompt 工程：对每个 LLM 调用节点做充分的 Prompt 优化和测试
3. 结构化输出：使用 JSON Schema / Pydantic 等强制输出格式
4. 重试机制：对可恢复的错误进行自动重试（指数退避）
5. 监控告警：每个节点的成功率、延迟、Token 消耗实时监控
6. A/B 测试：通过灰度发布逐步验证新版本

Agent 成功率保障：

1. 约束 Agent 行为空间：限制可用工具集、设置最大迭代次数、限制 Token 预算
2. Guardrails（护栏）：输入过滤 + 输出审核，防止异常行为
3. Few-shot 示例：在 System Prompt 中提供成功执行的范例
4. Self-Check 机制：在关键步骤后加入验证环节
5. Human-in-the-Loop：高风险决策前要求人工确认
6. 可观测性：详细记录每步推理和行动，便于事后分析
7. 评测体系：构建自动化评测集，对 Agent 定期回归测试
8. 模型选择：关键路径使用最强模型（如 Claude Opus / GPT-5），非关键路径使用轻量模型降本
9. 量化指标：任务完成率、端到端延迟 P95、平均推理步数、Token 

## 智能体模式是模型的自我迭代还是工作流（Workflow）的方式？

这个问题的本质是在问 Agent 的驱动力来源，答案是：两者的有机结合，但以模型的自主推理为核心特征。

模型自我迭代的维度：
- Agent Loop 的核心驱动力是 LLM 的推理能力
- 每次循环中，LLM 根据历史信息和当前状态自主决定下一步
- ReAct、Reflexion 等范式本质上是模型在"自我迭代"中不断改进输出
- 这是 Agent 区别于传统 Workflow 的根本特征

工作流的维度：
- Agent 系统的外部骨架仍然是一个工作流（Agent Loop 本身就是一种特殊的工作流）
- 工具注册、权限控制、错误处理等基础设施是工程化的工作流
- 多 Agent 系统的协作编排也是工作流性质的

正确理解：Agent 不是"纯靠模型自我迭代"也不是"纯 Workflow"，而是在 Workflow 骨架内赋予了模型自主决策的能力。Workflow 提供结构和约束，模型提供智能和灵活性。成熟的 Agent 系统一定是两者的平衡。

## 工作流是怎么搭建的？工作流怎么评测的？工作流的项目是怎么部署的？

搭建方式：

1. 代码方式（Code-first）：
  - LangGraph：将工作流建模为有向图，节点是处理函数，边是状态转移条件
  - 适合复杂逻辑和需要精细控制的场景
```
from langgraph.graph import StateGraph
graph = StateGraph(AgentState)
graph.add_node("classifier", classify_intent)
graph.add_node("retriever", retrieve_docs)
graph.add_node("generator", generate_answer)
graph.add_edge("classifier", "retriever")
graph.add_edge("retriever", "generator")
```
2. 低代码方式（Low-code）：
  - Dify / Coze / n8n / Flowise：拖拽式画布搭建
  - 适合快速原型和非技术团队

3. 配置驱动方式（Config-driven）：
  - YAML/JSON 定义工作流结构，代码实现节点逻辑
  - 适合需要动态修改流程的场景

评测方法：

1. 节点级评测：每个 LLM 节点单独构建 test set，评估准确率、格式一致性
2. 端到端评测：用真实用例跑完整流程，评估最终输出质量
3. 指标体系： 
  - 功能指标：任务完成率、输出质量（人工/自动评分）
  - 性能指标：延迟 P50/P95/P99、吞吐量
  - 成本指标：平均 Token 消耗 / 每次调用成本
  - 稳定性指标：成功率、重试率、异常率
4. 回归测试：每次 Prompt 或流程变更后执行自动化回归

部署架构：

- 中小规模：单体应用 + FastAPI 足够，部署在 Docker 容器中
- 大规模生产：微服务架构 
  - 拆分原则：每个 Agent / 核心工作流节点作为独立微服务
  - API Gateway → Agent Orchestrator → 各节点微服务（Classifier Service / Retriever Service / Generator Service）
  - 消息队列（Kafka/RabbitMQ）处理异步任务
  - Redis 做会话状态管理
  - 向量数据库集群做知识检索
  - Kubernetes 做容器编排和自动伸缩
- 推荐实践：从单体开始，当某个节点成为瓶颈时再拆分为微服务（避免过早微服务化带来的运维复杂度）

## 讲一下 Agent 中的"长短期记忆"
Agent 的记忆系统借鉴了认知科学中人类记忆的分层模型：

短期记忆（Short-term Memory / Working Memory）：

- 载体：LLM 的上下文窗口
- 容量：受模型上下文窗口限制（200K-1M tokens）
- 持续时间：单次会话内有效
- 内容：当前对话历史、工具调用结果、中间推理步骤
- 特点：高精度、即时可用、容量有限、会话结束即丢失
- 类比：人类的工作记忆，如同你在解题时脑海中暂存的信息

长期记忆（Long-term Memory）：

- 载体：向量数据库、关系数据库、文件系统
- 容量：理论上无限
- 持续时间：跨会话持久化
- 内容：用户画像、历史交互摘要、重要决策、知识沉淀
- 特点：需要检索才能使用、可能存在信息损失、需要定期维护更新
- 类比：人类的长期记忆，需要"回忆"才能激活

两者的协作机制：

1. 会话开始时，从长期记忆中检索与当前任务相关的信息，注入到短期记忆（上下文窗口）
2. 会话进行中，短期记忆不断更新
3. 会话结束或达到阈值时，从短期记忆中提取重要信息写入长期记忆
4. 形成闭环：长期记忆 → 检索 → 注入短期 → 推理交互 → 提取 → 更新长期记忆

## 什么样的信息应该放在长期记忆，什么样的信息放在短期记忆？

短期记忆（上下文窗口）适合存放：

- 当前对话的完整消息历史
- 当前任务的详细指令和约束
- 工具调用的原始返回结果
- 正在进行的推理链和中间步骤
- 临时性、一次性的信息（如"帮我查一下今天的天气"的结果）

长期记忆适合存放：

- 用户画像和偏好（"用户偏好 Python 而非 Java"、"用户是初级开发者"）
- 重要的历史决策和结论（"上次讨论后决定使用 PostgreSQL"）
- 项目级知识（架构设计、技术选型、关键约束）
- 交互模式（用户的沟通风格、常见需求模式）
- 实体关系（用户提到的人、项目、工具之间的关系）
- 错误和经验教训（"上次尝试 X 方案失败了，原因是 Y"）

## 如果要进行记忆压缩，通常有哪些方法？

系统化的记忆压缩方法论：

（1）LLM 摘要压缩
- 用 LLM 将长文本压缩为摘要
- 优点：语义保真度高；缺点：有信息损失风险，消耗额外 Token
- 实现：summary = llm("请将以下对话压缩为不超过200字的摘要，保留所有关键决策和结论：{context}")

（2）实体/关系提取
- 从文本中提取结构化的实体-关系三元组
- 存储为知识图谱：(用户, 偏好, Python), (项目A, 使用, PostgreSQL)
- 优点：高度结构化、检索效率高；缺点：可能丢失细微语境

（3）Token 级截断
- 最简单粗暴的方法，直接截断超出窗口的内容
- 策略：截断最早的消息 / 截断中间部分（保留首尾）
- 优点：零额外成本；缺点：信息完全丢失

（4）渐进式摘要（Progressive Summarization）
- 每隔 N 轮对话，对已有摘要和新对话进行合并摘要
- 形成递归压缩：L0（原文）→ L1（首次摘要）→ L2（再次摘要）

（5）选择性遗忘（Selective Forgetting）
- 基于重要性评分，优先保留高分信息，丢弃低分信息
- 重要性评估因素：与当前任务的相关性、信息的独特性、被引用的频率

（6）向量化压缩
- 将文本转为向量嵌入存储，需要时通过语义相似度检索
- 不保留原文，只保留语义表示
- 优点：存储效率高；缺点：检索时可能不精确

（7）混合策略（推荐）
- 最近 K 轮：保留原文
- K+1 到 2K 轮：LLM 摘要
- 更早的：实体提取 + 向量化存储
- 关键决策和用户偏好：始终保留原文

## 长期记忆的压缩触发条件是什么？是基于 Token 阈值还是基于语义重要性？

答案是两者结合，在实际工程中通常采用多条件触发机制：

基于 Token 阈值触发（最常用）：
- 当上下文窗口使用率达到 70-80% 时触发压缩
- 优点：实现简单、可预测
- 缺点：可能在关键信息还在积累时就被触发压缩

基于语义重要性触发（更智能）：
- 对每条信息进行重要性评分，当低重要性信息超过一定比例时触发压缩
- 评估维度：与核心目标的相关性、信息的时效性、被引用频率
- 优点：保留质量更高；缺点：评分本身消耗计算资源

基于事件触发：
- 会话结束时：将本次会话的重要信息写入长期记忆
- Git Commit 时（代码场景）：记录本次变更的上下文
- 任务完成时：记录任务结果和经验教训
- 定时触发：如每 30 分钟检查一次

## 多 Agent / 多异步任务下，如何防止上下文污染？

上下文污染（Context Contamination）指一个 Agent 或任务的上下文信息错误地泄漏到另一个 Agent 或任务中，导致推理错误。

防护策略：

（1）上下文隔离（Context Isolation）
- 每个 Agent 实例维护独立的上下文空间
- 禁止 Agent 之间直接共享原始上下文
- 使用消息传递（Message Passing）而非共享内存进行通信

（2）结构化消息传递
- Agent 之间通过明确定义的消息格式通信
- 消息只包含必要的结构化信息，不传递原始上下文
- 例如：Agent A 只传递"分析结果: {summary}"给 Agent B，而非整个对话历史

（3）命名空间隔离
- 为每个 Agent/任务分配独立的 Memory Namespace
- 存储时加上前缀：agent_A:key1, agent_B:key2
- 检索时只在本命名空间内搜索

（4）上下文快照与回滚
- 在关键分支点保存上下文快照
- 如果检测到污染，可以回滚到干净的快照点

（5）输入输出审计
- 每个 Agent 的输入和输出都经过Schema 校验
- 检测是否包含不应该出现的信息（如其他 Agent 的内部状态）

（6）会话级隔离（Session-level Isolation）
- 不同用户的 Agent 会话严格隔离
- 使用 session_id 作为所有操作的 partition key
- Redis 中使用独立的 key prefix 或 database

## 如何进行记忆管理，怎么处理长上下文，怎么进行持久化，后续怎么读取和关联？

这是一道综合题，需要端到端地回答整个记忆生命周期：

记忆管理全生命周期：

阶段一：采集与存储

```
对话消息 → 实时写入 Redis（短期，TTL=session_duration）
                ↓
会话结束 → 触发记忆提取 Pipeline：
  1. 关键信息提取（LLM）→ 结构化 JSON
  2. 用户偏好更新 → PostgreSQL
  3. 对话摘要生成 → 向量化 → Qdrant
  4. 实体关系提取 → 知识图谱（Neo4j / 或简单的 JSON）
```

阶段二：长上下文处理

```py
if total_tokens < 0.7 * max_window:
    # 无需处理，直接使用全量上下文
    pass
elif total_tokens < 0.9 * max_window:
    # 轻度压缩：对早期对话生成摘要
    compressed = summarize(messages[:oldest_k])
    messages = [compressed] + messages[oldest_k:]
else:
    # 重度压缩：只保留摘要 + 最近几轮
    summary = summarize(all_messages_except_recent_5)
    messages = [summary] + messages[-5:]
```

阶段三：持久化

```bash
存储层设计：
├── Redis（热存储）
│   ├── session:{session_id}:messages    # 当前会话消息
│   └── session:{session_id}:state       # Agent 状态
├── PostgreSQL（温存储）
│   ├── user_profiles                    # 用户画像
│   └── conversation_summaries           # 对话摘要
├── Milvus向量存储）
│   └── memory_embeddings                # 语义化记忆
└── S3/OSS（冷存储）
    └── raw_conversations                # 原始对话归档
```

阶段四：读取与关联

```py
def retrieve_context(user_id, current_query):
    # 1. 加载用户画像（PostgreSQL）
    profile = db.get_user_profile(user_id)
    
    # 2. 语义检索相关记忆（Qdrant）
    query_vector = embed(current_query)
    memories = qdrant.search(
        collection="memories",
        query_vector=query_vector,
        filter={"user_id": user_id},
        limit=5
    )
    
    # 3. 加载最近会话摘要（PostgreSQL）
    recent_summary = db.get_recent_summary(user_id, limit=3)
    
    # 4. 组装上下文
    context = assemble_context(
        system_prompt=base_prompt,
        user_profile=profile,
        relevant_memories=memories,
        recent_summary=recent_summary,
        current_messages=get_session_messages(session_id)
    )
    return context
```

## 存储时如果出现前后不一致的情况如何解决？

这是一个数据一致性问题，在分布式记忆系统中非常重要：

不一致的类型：

1. 时序不一致：用户先说"我用 Python"，后说"我转到 Go 了"
2. 事实矛盾：记忆中存储"项目使用 MySQL"，但新对话中说"我们用的是 PostgreSQL"
3. 并发写入冲突：多个 Agent 同时更新同一用户的记忆

解决策略：

（1）时间戳优先策略（Last Write Wins）
```py
def resolve_conflict(old_memory, new_memory):
    if new_memory.timestamp > old_memory.timestamp:
        return new_memory  # 新信息覆盖旧信息
    return old_memory
```

- 最简单有效，适合大部分场景

（2）LLM 智能合并

```py
def smart_merge(old_memory, new_memory):
    result = llm.call(f"""
    已有记忆：{old_memory}
    新信息：{new_memory}
    
    判断：
    1. 新信息是对已有记忆的更新/修正？→ 保留新信息
    2. 新信息与已有记忆描述不同方面？→ 合并两者
    3. 新信息与已有记忆矛盾且无法判断？→ 标记为待确认
    
    输出合并后的记忆。
    """)
    return result
```

（3）置信度评分机制

- 每条记忆附带置信度分数
- 多次提及 → 置信度上升
- 出现矛盾 → 降低旧记忆置信度
- 查询时按置信度加权

（4）向用户确认
- 当检测到关键信息矛盾时，主动向用户确认
- "我记得您之前提到使用 MySQL，但刚才您说用的是 PostgreSQL，请问哪个是正确的？"

（5）多版本共存 + 上下文决定
- 同一主题保留多个版本
- 在具体使用时根据当前上下文选择最相关的版本

## 你了解的 Tool 调用机制是怎样的？

Tool Calling 是 Agent 与外部世界交互的核心桥梁，也是 Agent 区别于普通聊天机器人的关键能力。其机制可以分为三个层面理解：

**协议层**：LLM 厂商定义了标准化的工具描述格式（通常是 JSON Schema），包括工具名称、功能描述、参数定义。这些描述被注入到 System Prompt 或特殊的 tools 参数中，告诉模型"你有哪些工具可以用"。

**决策层**：模型在推理过程中，根据用户的请求和工具描述，决定是否需要调用工具、调用哪个工具、传入什么参数。模型输出的不是普通文本，而是一个结构化的 Tool Call 对象（包含工具名和参数 JSON）。

**执行层**：应用层代码（Agent 框架或自定义代码）解析模型输出的 Tool Call，调用对应的真实函数或 API，获取返回结果，再将结果作为新的消息（tool_result）回传给模型，模型基于结果继续推理或生成最终回答。

## 介绍一下 Function Call 原理，模型生成的 JSON 如何通过逻辑触发表层代码执行并返回给模型？

模型是如何知道该调用哪个工具的？

这是一个非常关键的底层问题，需要从训练和推理两个阶段回答：

训练阶段：
- 模型在 SFT（有监督微调）和 RLHF 阶段被训练了大量的"工具调用"样本
- 训练数据包含：用户请求 + 工具描述 → 正确的 tool_call JSON 输出
- 模型学会了根据用户意图和工具描述之间的语义匹配来选择工具
- 本质上是指令跟随 + 语义匹配能力的结合

推理阶段的决策机制：
1. 工具描述作为 System Prompt 的一部分被注入上下文
2. 模型看到用户请求后，进行语义理解
3. 将用户意图与每个工具的 description 和 parameters 做语义匹配
4. 如果匹配度高，模型决定输出特殊的 tool_call 格式（而非普通文本）
5. 参数提取：模型从用户输入中抽取与工具参数 Schema 对应的值

## MCP 和 Function Calling 的区别

一句话总结：Function Calling 是"模型调用工具的能力"，MCP 是"工具如何被标准化暴露和发现的协议"。Function Calling 解决的是"怎么调用"，MCP 解决的是"调用什么"和"如何连接"。MCP 的底层执行仍然依赖 Function Calling。

类比：Function Calling 好比 USB 接口的电气协议，MCP 好比 USB 的标准规范（包括接口形状、供电标准、设备发现协议等）。

## MCP 协议的核心内容、介绍一下 MCP

MCP（Model Context Protocol） 是 Anthropic 于 2024 年 11 月推出的开放标准，旨在标准化 AI 系统与外部工具和数据源的集成方式。2025 年 12 月，Anthropic 将 MCP 捐赠给 Linux Foundation 下的 Agentic AI Foundation（AAIF），OpenAI 和 Block 作为联合创始成员。

核心架构（三角色模型）：
- Host（宿主）：用户交互的应用（如 Claude Desktop、Cursor、ChatGPT）
- Client（客户端）：Host 内部的 MCP 客户端，负责与 MCP Server 通信
- Server（服务器）：暴露工具和数据的服务端（如 GitHub MCP Server、Slack MCP Server）

协议提供的四大能力：
1. Tools（工具）：可执行的函数，如搜索、数据库查询、文件操作
2. Resources（资源）：可读取的数据源，如文件内容、数据库记录
3. Prompts（提示模板）：预定义的 Prompt 片段，可被 Client 调用
4. Sampling（采样）：Server 可以请求 Client 的 LLM 进行推理

技术规范：
- 传输协议：JSON-RPC 2.0 over HTTP（Streamable HTTP）或 stdio（本地进程）
- 授权框架：OAuth 2.1 + OpenID Connect
- 2025.11 规范新增：异步任务（Tasks）、增量权限协商、Server Identity

行业采用情况（截至 2026 年 3 月）：
- 每月 SDK 下载量超 9700 万次（Python + TypeScript）
- 超过 10,000 个活跃 MCP Server
- 主流 Client 支持：Claude、ChatGPT、Cursor、Gemini、VS Code、Microsoft Copilot
- 2026 年路线图聚焦四大方向：Streamable HTTP 演进、Agent 协作、Tasks 成熟、企业就绪

## MCP 和 Skill 的区别，二者谁占用上下文窗口比较大？

概念区分：

MCP：是标准化的工具暴露协议，通过 Client-Server 架构连接。工具描述（Schema）注入上下文窗口，实际执行发生在 Server 端。

Skill（技能）：通常指在 System Prompt 或配置文件中预定义的能力描述和行为指南。例如 Cursor 的 Rules、Coze 的 Skills。Skill 更像是 Prompt 层面的"能力定义"，告诉模型如何完成特定类型的任务。

上下文窗口占用对比：
- Skill 通常占用更大。因为 Skill 本质是详细的 Prompt 指令，可能包含角色定义、行为规范、示例（few-shot）、限制条件等，动辄数百到数千 Token。
- MCP 工具描述通常较精简，每个工具的 Schema（name + description + parameters）一般在 100-300 Token。
- 但如果接入了大量 MCP Server（每个暴露多个工具），工具描述的总量也会很大。
最佳实践：只加载当前任务需要的工具和 Skill，避免全量注入。LangGraph 等框架支持动态工具加载。

## Skills 是怎么实现的，Skills 和 MCP 区别，怎么使用它们？

Skills 的实现方式：

Skills 本质上是结构化的 Prompt 模板 + 关联的工具集合 + 执行逻辑。

Skills vs MCP 的核心区别：

Skills 是"教 Agent 如何做事"（知识和方法论层面），MCP 是"给 Agent 提供做事的工具"（能力和资源层面）。一个好的 Agent 需要两者结合：Skill 提供做事的方法论，MCP 提供做事的工具。

## Multi-Agent，你是怎么做意图识别的？

Multi-Agent 系统概述：

Multi-Agent 系统通过多个专业化 Agent 的协作来解决复杂问题。核心挑战之一就是意图识别——准确理解用户意图并路由到正确的 Agent。

意图识别的实现方式：

### 方案一：LLM Router（主流方案）

```py
ROUTER_PROMPT = """你是一个意图路由器。根据用户输入，判断应该由哪个 Agent 处理。

可用 Agent：
1. code_agent: 处理代码编写、调试、代码审查相关任务
2. data_agent: 处理数据分析、可视化、报表生成相关任务
3. research_agent: 处理信息检索、调研、资料整理相关任务
4. writing_agent: 处理文案撰写、文档编辑、翻译相关任务

输出 JSON: {"agent": "agent_name", "confidence": 0.0-1.0, "reasoning": "..."}
"""

def route(user_input):
    result = llm.call(ROUTER_PROMPT + f"\n\n用户输入：{user_input}")
    routing = json.loads(result)
    if routing["confidence"] < 0.7:
        return fallback_agent  # 低置信度走兜底
    return get_agent(routing["agent"])
```

### 方案二：嵌入相似度 + 分类器（低延迟方案）

```py
# 预处理：为每个 Agent 的能力描述生成嵌入
agent_embeddings = {
    "code_agent": embed("代码编写 调试 审查 编程 bug修复"),
    "data_agent": embed("数据分析 可视化 图表 报表 统计"),
    # ...
}

# 运行时
user_embedding = embed(user_input)
scores = {name: cosine_similarity(user_embedding, emb) 
          for name, emb in agent_embeddings.items()}
best_agent = max(scores, key=scores.get)
```

### 方案三：关键词 + 规则引擎（确定性方案）

- 适合领域明确、意图有限的场景
- 正则匹配 + 关键词词典 + 规则优先级
- 优点：零延迟、100% 可预测

实际项目推荐：规则兜底 + LLM Router 组合。先用规则匹配高确定性意图，匹配不上再走 LLM Router。

## Skill 和 Agent 的关系，为什么不用 Skill 而用子 Agent？

关系：Skill 是 Agent 的能力单元，Agent 可以拥有多个 Skill。Skill 是"技能"，Agent 是"角色"。

为什么某些场景需要子 Agent 而非 Skill？

选择子 Agent 的判断标准：
- 子任务需要大量独立上下文（如分析一份长文档）→ 子 Agent
- 子任务需要不同的工具集或不同的模型 → 子 Agent
- 多个子任务可以并行执行 → 子 Agent
- 子任务的失败不应影响主流程 → 子 Agent（错误隔离）
- 子任务简单、不需要独立上下文 → Skill 即可

##  ReAct / 反思 / 任务规划

你设计的 Agent 是怎么实现 ReAct 模式的？

实现架构：

```py
class ReActAgent:
    def __init__(self, llm, tools, max_iterations=10):
        self.llm = llm
        self.tools = {t.name: t for t in tools}
        self.max_iterations = max_iterations
    
    def run(self, query):
        messages = [{"role": "system", "content": self.system_prompt}]
        messages.append({"role": "user", "content": query})
        
        for i in range(self.max_iterations):
            # 1. Think - LLM 推理
            response = self.llm.call(messages, tools=list(self.tools.values()))
            
            # 2. 检查是否为最终回答
            if not response.tool_calls:
                return response.content  # 最终答案
            
            # 3. Act - 执行工具
            messages.append(response.message)  # 记录 assistant 的 tool_call
            
            for tool_call in response.tool_calls:
                try:
                    result = self.tools[tool_call.name].execute(tool_call.args)
                except Exception as e:
                    result = f"工具执行失败: {str(e)}"
                
                # 4. Observe - 注入观察结果
                messages.append({
                    "role": "tool",
                    "tool_call_id": tool_call.id,
                    "content": str(result)
                })
        
        return "达到最大迭代次数，以下是目前收集的信息：..." + self._summarize(messages)
```

关键设计决策：

- System Prompt 中的 ReAct 指令：明确要求模型先思考（Thought），再决定行动（Action），观察结果后再思考
- 工具描述质量：每个工具的 description 是 Agent 准确选择的关键
- 错误恢复：工具失败时不终止，而是将错误信息返回给模型，让模型自行决定换工具或换策略
- 循环退出：除最大迭代次数外，还可以检测连续相同工具调用（死循环检测）

## 什么是 Agent 的反思机制？

反思机制（Reflection） 是让 Agent 在生成输出后进行自我审视和改进的能力。

实现方式：

```py
# 两阶段反思
def generate_with_reflection(query, context):
    # 阶段一：生成初始回答
    initial_response = llm.call(f"请回答：{query}", context=context)
    
    # 阶段二：反思审查
    reflection = llm.call(f"""
    请审查以下回答的质量：
    
    用户问题：{query}
    初始回答：{initial_response}
    
    检查维度：
    1. 事实准确性：回答中是否有明显错误？
    2. 完整性：是否遗漏了重要信息？
    3. 语气适当性：语气是否专业、温和、得体？
    4. 逻辑一致性：回答是否自相矛盾？
    
    如果发现问题，请输出改进后的版本。
    如果没有问题，输出"APPROVED"。
    """)
    
    if "APPROVED" in reflection:
        return initial_response
    else:
        return reflection  # 改进后的版本
```

## 如何处理异常情况？比如路由到了一个错误的任务，用户说不对，Agent 会不会纠正自己的行为？

是的，成熟的 Agent 系统必须支持用户反馈驱动的自我纠正。

```py
class SelfCorrectingAgent:
    def handle_user_feedback(self, feedback):
        if self.detect_correction(feedback):
            # 1. 承认错误
            response = "抱歉理解有误。"
            
            # 2. 分析错误原因
            error_analysis = self.llm.call(f"""
            用户原始请求：{self.original_query}
            我的理解：{self.last_routing_decision}
            用户反馈：{feedback}
            
            分析我理解错误的原因，并重新判断用户的真正意图。
            """)
            
            # 3. 重新路由
            new_route = self.re_route(self.original_query, feedback, error_analysis)
            
            # 4. 记录错误案例（用于改进）
            self.error_log.append({
                "query": self.original_query,
                "wrong_route": self.last_routing_decision,
                "correct_route": new_route,
                "user_feedback": feedback
            })
            
            return self.execute(new_route)
```

其他异常处理策略：

- 超时：设置每步超时，超时后用 fallback 响应
- 工具调用失败：重试 → 换工具 → 降级处理
- 模型输出格式错误：解析失败时自动重试，并在 Prompt 中强调格式要求
- 死循环检测：连续 3 次相同操作触发退出

## 当 Agent 工具的某一节点出现问题时的解决方法

分层处理策略：
```
Level 1 - 自动重试：
  if error_type == "timeout" or error_type == "rate_limit":
      retry with exponential backoff (1s, 2s, 4s)
      max_retries = 3

Level 2 - 工具降级：
  if primary_tool fails after retries:
      switch to fallback_tool
      e.g., Google Search → Bing Search → 缓存结果

Level 3 - Agent 自主恢复：
  将错误信息返回给 LLM，让其决定替代方案
  "搜索工具暂时不可用，请用你的已有知识回答，并标注可能不是最新信息"

Level 4 - 人工介入：
  if critical_failure:
      notify_human_operator()
      return "当前处理遇到技术问题，已转交人工处理"
```

## 工具调用异常、超时后的回滚逻辑是在 Agent 服务内实现的吗？
  
回滚逻辑在 Agent 服务内实现，而非在工具层

## 错误检测与回滚机制的作用是什么？

作用：
1. 保证数据一致性：避免"做了一半"的不完整状态
2. 提升系统可靠性：自动恢复能力减少人工干预
3. 用户体验保障：对用户透明地处理错误，而非返回技术错误信息
4. 成本控制：及时中止无效操作，避免浪费更多资源
5. 可观测性：错误检测记录提供问题诊断的数据基础

## Agent 存在什么安全问题？

六大安全威胁：

① Prompt Injection（提示词注入）
- 攻击者在用户输入或外部数据中嵌入恶意指令
- 间接注入：通过网页、文档等外部数据源注入
- 危害：绕过安全限制、泄露 System Prompt、执行未授权操作

② 工具滥用（Tool Misuse）
- Agent 被诱导执行危险操作（删除文件、发送邮件、执行恶意代码）
- 授权范围过大导致攻击面增大

③ 数据泄露（Data Leakage）
- Agent 将敏感信息（API Key、用户数据、内部知识）泄露到输出中
- 通过精心构造的 Prompt 提取 System Prompt 内容

④ 模型窃取/投毒（Model Stealing/Poisoning）
- 通过大量查询反推模型的 System Prompt 和配置
- 在训练数据或 RAG 知识库中注入误导性信息

⑤ 幻觉风险（Hallucination Risk）
- Agent 自信地执行基于幻觉信息的操作
- 在 Agent 场景中，幻觉直接导致错误行动（而非仅仅错误回答）

⑥ 权限提升（Privilege Escalation）
- Agent 通过组合多个低权限工具实现高权限操作
- 如：读取配置文件 → 获取数据库密码 → 直接访问数据库

## 工业级幻觉减少方案：

（1）RAG（检索增强生成）— 最核心
- 回答必须基于检索到的真实文档/数据
- 在 Prompt 中明确指令："只根据以下提供的信息回答，如果信息不足请说明"
- 检索质量直接影响幻觉率（所以 RAG Pipeline 的优化至关重要）

（2）Grounding（接地）
- 将 LLM 的输出与真实数据源进行"接地"验证
- 如：LLM 说"该产品售价 299 元" → 查询数据库验证真实价格

（3）Self-Consistency（自一致性）
- 对同一问题多次采样，取一致性最高的答案
- 减少随机幻觉的影响

（4）输出后处理
- 事实检查模块：提取输出中的事实声称，逐一验证
- 数值校验：涉及数字的内容与数据源比对
- 逻辑一致性检查：检测输出中的自相矛盾

（5）Prompt Engineering
- "如果你不确定答案，请明确说'我不确定'而非编造答案"
- "请在回答中标注每个事实的来源"
- "如果提供的上下文信息不足以回答问题，请如实告知"

（6）模型选择
- 使用幻觉率更低的模型（GPT-5 系列声称幻觉率降低 80%）
- 对关键路径使用最强模型

## 智能体测试与一般测试的区别

智能体测试的特殊要求：

- 多次执行取统计结果（而非单次判断）
- 需要 LLM-as-Judge 或人工评分
- 需要测试鲁棒性（同义改写、噪声输入）
- 需要对抗性测试（Prompt Injection 等）

## 如何写好的 Prompt？Prompt 设计的规则

好的 Prompt 是 Agent 系统最核心的"软件"。大厂实践中，Prompt 设计遵循以下体系化规则：

六大核心原则：

原则一：角色定义清晰

```
✗ "帮我分析一下数据"
✓ "你是一名拥有 10 年经验的资深数据分析师，擅长 Python/SQL。
   你的分析风格注重数据驱动，总是先提出假设再验证。"
- 角色定义锚定模型的行为模式和输出风格
- 加入"专业年限"和"风格特征"能显著提升输出质量
```

原则二：指令具体明确

```
✗ "总结一下这篇文章"
✓ "请用 3 个要点总结这篇文章的核心论点，每个要点不超过 50 字，
   使用'首先/其次/最后'的结构，面向非技术背景的管理层读者。"
- 明确输出格式、长度、受众、结构
```

原则三：提供示例（Few-shot）

```
示例输入：用户说"这个产品太垃圾了"
示例输出：{"sentiment": "negative", "intensity": 0.9, "topic": "product_quality"}

现在分析：用户说"客服态度不错但等太久了"
- Few-shot 是提升格式一致性和任务理解的最有效手段
```

原则四：使用分隔符和结构标签

```
<task>代码审查</task>
<input_code>
{用户代码}
</input_code>
<review_criteria>
1. 安全漏洞 2. 性能问题 3. 代码规范
</review_criteria>
<output_format>JSON</output_format>
- XML/Markdown 标签清晰划分 Prompt 的不同部分
- 防止模型混淆指令和数据
```

原则五：约束与兜底

```
重要规则：
- 如果信息不足以回答，请明确说"信息不足，无法回答"
- 不要编造数据或引用来源
- 如果用户要求超出你的能力范围，请说明并建议替代方案
- 明确告诉模型"不该做什么"与"该做什么"同样重要
```

原则六：思维链引导

```
请按以下步骤分析：
Step 1: 理解用户的核心需求
Step 2: 识别可能的解决方案
Step 3: 评估每个方案的优劣
Step 4: 给出最终推荐并说明理由
```

- 分步骤引导可以显著提升复杂推理任务的质量

Prompt 模板结构（大厂标准）：

```
[角色定义] → [任务描述] → [上下文/背景] → [约束条件] → [输出格式] → [示例] → [用户输入]
```

## 如何优化 Prompt Engineering 以减少前端请求的 Token 消耗？

Token 消耗直接影响成本和延迟，以下是系统化的优化策略：

（1）System Prompt 精简
```
优化前（800 tokens）：
"你是一个非常专业的、经验丰富的、在人工智能领域有深入研究的数据分析师，
 你擅长使用Python语言编写代码，同时也精通SQL查询语言...（冗长描述）"

优化后（200 tokens）：
"角色：资深数据分析师。技能：Python, SQL, 可视化。风格：简洁、数据驱动。"
- 去除冗余修饰词，保留核心信息
- 实测：精简后效果几乎不变，但 Token 减少 60-70%
```

（2）动态 Prompt 组装
```py
def build_prompt(task_type, user_input):
    base = load_base_prompt()  # 通用部分（200 tokens）
    
    # 仅加载当前任务需要的部分
    if task_type == "code_review":
        base += load_module("code_review_rules")  # 150 tokens
    elif task_type == "data_analysis":
        base += load_module("data_analysis_rules")  # 120 tokens
    
    # 而非一次性加载所有模块（800+ tokens）
    return base
```

（3）Few-shot 示例优化
- 只保留 1-2 个最典型的示例（而非 5-10 个）
- 使用最短的能说明问题的示例
- 对于格式简单的任务，用格式说明替代示例

（4）上下文窗口管理
- 历史消息压缩（前文已述）
- 工具返回结果截断（只保留关键数据）
- RAG 结果精简（只注入最相关的 Top-3 段落）

（5）输出约束
```
"请用不超过 100 字回答" → 直接减少输出 Token
"输出 JSON，不要解释" → 避免冗长的说明性文字
```

（6）Prompt 缓存
- 利用模型的 Prompt Caching 功能（如 Anthropic 的 Prompt Caching）
- 静态 System Prompt 部分只计费一次
- 对于高频相似请求，显著降低成本

## 对于模型的选型你是否有考虑呢？（不同任务采用不同模型）

模型选型的决策框架：
```
任务类型 × 质量要求 × 延迟要求 × 成本预算 → 最优模型
```
分任务推荐（2026 年 3 月版本）：

大厂实践中的混合模型策略：
```
class ModelRouter:
    def select_model(self, task):
        if task.complexity == "high" and task.quality_requirement == "critical":
            return "claude-opus-4-6"      # 最强模型，不惜成本
        elif task.type == "code":
            return "claude-sonnet-4-6"     # 代码任务性价比最高
        elif task.latency_requirement < 1.0:  # 秒级响应
            return "claude-haiku-4-5"      # 最快
        elif task.type == "classification":
            return "fine-tuned-classifier" # 专用小模型
        else:
            return "claude-sonnet-4-6"     # 默认选择
```

## 需要实现一个任务，四种方式（微调/换更大模型/上下文工程/提示词工程），哪个性价比最高？

四种方式的全面对比：

性价比排序（一般情况）：

```
Prompt 工程 > 上下文工程（RAG） > 换更大模型 > 微调
```

决策流程：

```
Step 1: 先优化 Prompt（成本最低，2-3天能完成）
  → 效果达标？→ 结束
  → 效果不足？→ 继续

Step 2: 加入上下文工程（RAG/Few-shot动态注入，1-2周）
  → 效果达标？→ 结束
  → 效果不足？→ 继续

Step 3: 尝试更强的模型（几小时切换）
  → 效果达标？评估成本能否接受 → 结束
  → 效果不足或成本太高？→ 继续

Step 4: 微调（需要高质量标注数据，2-4周）
  → 适合场景：任务高度特化、数据充足、推理量大（微调小模型替代大模型可省成本）
```

关键洞察：LangChain 2025 年调研显示，57% 的组织不做微调，而是依赖基础模型 + Prompt 工程 + RAG。微调在大多数应用场景中不是必需的。

## 如果换一个参数量更大的模型，会不会比微调好？

答案：不一定，取决于具体场景。

更大模型更好的场景：
- 任务需要广泛的通用能力（如开放式对话、通用问答）
- 没有足够的高质量标注数据进行微调
- 任务变化频繁，微调的模型需要频繁更新
- 需要多语言、多领域的泛化能力

微调更好的场景：
- 任务高度特化（如特定行业的实体识别、特定格式的输出）
- 有大量高质量标注数据（>1000 条）
- 推理量极大，需要用小模型降成本（微调 7B 模型达到 70B 模型在特定任务上的效果）
- 需要特定的输出风格或格式一致性
- 有严格的延迟要求（大模型推理慢）

经验法则：
- 先试大模型 + 好的 Prompt → 如果效果差距在 5% 以内，不值得微调
- 如果效果差距 >10%，且有充足数据，考虑微调
- 微调的"甜蜜点"：用中等规模模型（7B-13B）微调，在特定任务上达到或超过大模型效果，同时推理成本低数倍

## 什么是模型预热（Model Warm-

模型预热是指在正式服务请求前，通过发送预设请求让模型完成初始化加载，避免首次请求的高延迟。
为什么需要预热：

1. 模型加载延迟：大模型首次加载到 GPU 需要数十秒
2. KV Cache 初始化：首次推理需要初始化注意力缓存
3. CUDA 编译：部分算子首次执行时需要 JIT 编译
4. 连接池建立：API 调用需要建立 TCP 连接池

## Agent 上线后的持续性挑战：

1. 长尾问题：总有预料之外的用户输入，需要持续收集 bad case 并优化
2. 模型漂移：API 模型更新可能导致行为变化，需要回归测试监控
3. 成本优化：监控 Token 消耗趋势，识别优化点（缓存、Prompt 精简、模型降级）
4. 知识库更新：RAG 知识库需要定期更新，保持信息时效性
5. 用户反馈闭环：建立"反馈→分析→改进→验证"的持续优化循环
6. 安全对抗：Prompt Injection 攻击手段不断演进，安全策略需要持续更新
7. 可观测性完善：根据线上问题补充监控指标和告警规则
8. 合规审计：定期审查 Agent 行为是否符合业务合规要求

## 长文本生成的技术方案

当需要生成超出模型单次输出限制（如 4K-64K Token）的长文本时：

方案一：分段生成 + 拼接

```py
def generate_long_text(outline):
    sections = []
    for section in outline:
        prompt = f"""
        文章整体大纲：{outline}
        已生成的内容摘要：{summarize(sections)}
        
        请生成以下章节的完整内容：
        {section.title}
        {section.requirements}
        
        注意与前文的衔接和一致性。
        """
        content = llm.generate(prompt)
        sections.append(content)
    return "\n\n".join(sections)
```

方案二：大纲→扩展→润色三阶段

```
Stage 1: 生成详细大纲（含每节的要点和字数要求）
Stage 2: 逐节扩展为完整内容
Stage 3: 全局润色（检查一致性、修正衔接）
```

方案三：利用长输出模型

- Claude Opus 4.6 支持 64K 输出 Token（约 5 万中文字）
- GPT-5.2 支持 128K 输出 Token
- 对于长度在模型输出限制内的文本，可以一次性生成


关键挑战：
- 前后一致性：分段生成时每段需要"看到"前文的摘要
- 风格统一：不同段落的语气和风格可能不一致
- 结构完整：确保总分总结构，不遗漏章节

推荐方案：大纲驱动 + 分段生成 + 全局审校。这是目前最稳定的长文本生成方案。