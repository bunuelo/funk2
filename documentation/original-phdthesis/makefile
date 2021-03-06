default: phdthesis.pdf

phdthesis.pdf: \
  makefile \
  phdthesis.tex \
  bibliography.bib \
  frontbackmatter/abstract.tex \
  frontbackmatter/acknowledgments.tex \
  frontbackmatter/bibliography.tex \
  frontbackmatter/colophon.tex \
  frontbackmatter/contents.tex \
  frontbackmatter/declaration.tex \
  frontbackmatter/dedication.tex \
  frontbackmatter/dirtytitlepage.tex \
  frontbackmatter/preface.tex \
  frontbackmatter/publication.tex \
  frontbackmatter/titleback.tex \
  frontbackmatter/titlepage.tex \
  chapters/introduction.tex \
  chapters/modelling_the_continuously_dynamic.tex \
  chapters/learning_causal_hypotheses.tex \
  chapters/layers_of_reflective_thinking.tex \
  chapters/learning_from_success_and_failure.tex \
  chapters/problematic_interpretations.tex \
  chapters/related_models.tex \
  chapters/introducing_simulation.tex \
  chapters/graph_notation.tex \
  chapters/symbolic_representation.tex \
  chapters/grounded_factual_knowledge.tex \
  chapters/hypotheses_and_counterfactual_knowledge.tex \
  chapters/the_planning_machine.tex \
  chapters/learning_search_heuristics.tex \
  chapters/related_simulations.tex \
  chapters/introducing_computation.tex \
  chapters/computational_activities_in_duration.tex \
  chapters/causally_reflective_procedural_tracing.tex \
  chapters/the_mind_monitor_application.tex \
  chapters/related_implementations.tex \
  chapters/evaluation.tex \
  chapters/future.tex \
  chapters/science.tex \
  chapters/education.tex \
  chapters/causal_reflective_tracing_tutorial.tex \
  chapters/the_code.tex \
  gfx/agent_environment.pdf \
  gfx/blocks_world_screenshot-1.pdf \
  gfx/combinatorial_explosion_example.pdf \
  gfx/combinatorial_explosion_example_with_heuristics.pdf \
  gfx/dependency_traces.pdf \
  gfx/tracing_bug_dependencies.pdf \
  gfx/communication_theory.pdf \
  gfx/concurrent_parallel_reflection_efficiency.pdf \
  gfx/difference_engine_feedback_control.pdf \
  gfx/environment_perception_physical.pdf \
  gfx/feedback_control.pdf \
  gfx/frame_perception.pdf \
  gfx/frame_representation.pdf \
  gfx/goal_state.pdf \
  gfx/infer_plan_effects.pdf \
  gfx/ladder_state_machine.pdf \
  gfx/learning_to_plan.pdf \
  gfx/learning_to_plan-1-goal_oriented_action_hypotheses.pdf \
  gfx/learning_to_plan-2-action_precondition_goal_occurrence_hypotheses.pdf \
  gfx/learning_to_plan-3-action_precondition_transframe_hypotheses.pdf \
  gfx/learning_to_plan-4-goal_occurrence_physical_hypotheses.pdf \
  gfx/learning_to_plan-four_step_cycle.pdf \
  gfx/mindmon-isis_world-screenshot-1.pdf \
  gfx/model-6.pdf \
  gfx/simulation_example_state.pdf \
  gfx/simulation_reflective_1_example_state.pdf \
  gfx/reflective_relationship_visualization.pdf \
  gfx/example_symbolic_reference_to_physical_activity.pdf \
  gfx/example_symbolic_memory.pdf \
  gfx/example_second_order_symbol.pdf \
  gfx/two_example_grounded_symbolic_references.pdf \
  gfx/example_simultaneity.pdf \
  gfx/example_transition.pdf \
  gfx/example_resource.pdf \
  gfx/example_resource_conflict.pdf \
  gfx/example_resource_activation.pdf \
  gfx/example_second_order_resource.pdf \
  gfx/example_transframe.pdf \
  gfx/example_hypothesis.pdf \
  gfx/example_conjunctive_hypothesis_space.pdf \
  gfx/example_conjunctive_version_space.pdf \
  gfx/example_counterfactual_transframe.pdf \
  gfx/example_plan_operators.pdf \
  gfx/example_plan.pdf \
  gfx/example_planner.pdf \
  gfx/example_plan_failure.pdf \
  gfx/example_critical_failure_heuristic.pdf \
  gfx/example_counterfactual_simultaneity.pdf \
  gfx/example_causal_knowledge.pdf \
  gfx/example_causal_hypothesis.pdf \
  gfx/example_global_environment.pdf \
  gfx/implemented_mindmon.pdf \
  gfx/implemented_physical_knowledge.pdf \
  gfx/implemented_reflective_knowledge.pdf \
  gfx/implemented_planning_machine_knowledge.pdf \
  gfx/implemented_semantic_event_knowledge_base.pdf \
  gfx/implemented_reflective_event_knowledge_base.pdf \
  gfx/implemented_isisworld_first_order_resource_activator.pdf \
  gfx/implemented_first_order_resource_activator.pdf \
  gfx/implemented_first_order_plan_activator.pdf \
  gfx/implemented_second_order_resource_activator.pdf \
  gfx/simulation_example_state_graph.pdf \
  gfx/basic_frame_object_types.pdf \
  gfx/multiple_agent_environment.pdf \
  gfx/objective_description.pdf \
  gfx/partially_observable.pdf \
  gfx/perception_categorization.pdf \
  gfx/physical_perception.pdf \
  gfx/planning_machine_operations.pdf \
  gfx/planning_machine_reflective_knowledge.pdf \
  gfx/problem_complexity_versus_algorithm_adaptability.pdf \
  gfx/reflective_event_representation.pdf \
  gfx/reinforcement_learning.pdf \
  gfx/serial_and_parallel_plan.pdf \
  gfx/state_action.pdf \
  gfx/transframe.pdf \
  gfx/fibermon_many_fibers.pdf \
  gfx/magritte_pipe.pdf
	pdflatex phdthesis
	bibtex   phdthesis
	pdflatex phdthesis
	pdflatex phdthesis

%.pdf: %.neato makefile
	neato $< -Tpdf > $@

%.pdf: %.dot makefile
	dot -Txdot $< | dot2tex -c -d -ftikz -traw > temp.tex
	pdflatex temp.tex
	rm -f temp.tex
	mv -f temp.pdf $@

%.pdf: %.png makefile
	pngtopnm $< > $<.pnm
	pnmtops $<.pnm > $<.ps
	epstopdf $<.ps -o $@
	#pstopdf --resolution=print --convert $<.ps
	#mv -f $<.pdf $@
#	rm -f $<.pnm
#	rm -f $<.ps

clean:
	rm -f phdthesis.pdf
	rm -f chapters/*.aux
	rm -f frontbackmatter/*.aux
	rm -f phdthesis.aux
	rm -f phdthesis.lof
	rm -f phdthesis.log
	rm -f phdthesis.lol
	rm -f phdthesis.lot
	rm -f phdthesis.out
	rm -f phdthesis.toc
	rm -f phdthesis.bbl
	rm -f phdthesis.blg

