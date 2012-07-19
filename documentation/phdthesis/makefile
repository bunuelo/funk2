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
  chapters/grounded_knowledge.tex \
  chapters/hypothetical_knowledge.tex \
  chapters/learning_search_heuristics.tex \
  chapters/related_simulations.tex \
  chapters/the_implementation.tex \
  chapters/the_substrate_for_accountable_layered_systems.tex \
  chapters/related_implementations.tex \
  chapters/evaluation.tex \
  chapters/future.tex \
  chapters/science.tex \
  chapters/education.tex \
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
  gfx/two_example_grounded_symbolic_references.pdf \
  gfx/example_simultaneity.pdf \
  gfx/example_transition.pdf \
  gfx/example_resource_conflict.pdf \
  gfx/example_resource.pdf \
  gfx/example_transframe.pdf \
  gfx/example_causal_knowledge.pdf \
  gfx/example_causal_hypothesis.pdf \
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
  gfx/fibermon_many_fibers.pdf
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

